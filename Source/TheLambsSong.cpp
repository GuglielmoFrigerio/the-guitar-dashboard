/*
  ==============================================================================

    TheLambsSong.cpp
    Created: 21 Aug 2021 7:04:54pm
    Author:  gugli

  ==============================================================================
*/

#include "TheLambsSong.h"
#include "MidiTrack.h"
#include "VirtualBand.h"
#include "PlayerComponent.h"
#include "GuitarDashCommon.h"
#include "SamplesTrack.h"


void TheLambsSong::nextMarker(juce::AudioTransportSource* pAudioTransportSource)
{
    if (!m_backingTrackMarkers.empty()) {
        auto songPosition = pAudioTransportSource->getCurrentPosition();
        for (auto& marker : m_backingTrackMarkers) {
            if (marker.getPosition() > songPosition) {
                marker.activate(pAudioTransportSource);
                break;
            }
        }
    }
}

void TheLambsSong::previousMarker(juce::AudioTransportSource* pAudioTransportSource)
{
    if (!m_backingTrackMarkers.empty()) {
        auto songPosition = pAudioTransportSource->getCurrentPosition() - m_previousGuardTime;
        BackingTrackMarker* pCandidateMarker = nullptr;
        for (auto& marker : m_backingTrackMarkers) {
            if (marker.getPosition() < songPosition)
                pCandidateMarker = &marker;
            else break;
        }
        if (pCandidateMarker != nullptr)
            pCandidateMarker->activate(pAudioTransportSource);
    }
}

void TheLambsSong::updateMarkers(double position, PlayerComponent* pPlayerComponent)
{
    if (!m_backingTrackMarkers.empty()) {
        auto previousEnabled = false;
        auto nextEnabled = false;

        auto positionForPrevious = position - m_previousGuardTime;

        for (auto& marker : m_backingTrackMarkers) {
            auto markerPosition = marker.getPosition();
            if (markerPosition > position)
                nextEnabled = true;
            if (markerPosition < positionForPrevious)
                previousEnabled = true;
        }

        pPlayerComponent->updateMakerButtons(previousEnabled, nextEnabled);
    }

}

juce::String TheLambsSong::getTrackPath()
{
    return m_resourcesPath + juce::String("Tracks/") + m_trackName;
}

void TheLambsSong::loadMidiTracks()
{
    std::string inputFilename = "../../Resources/sample.mid";
    auto midiFilePtr = loadMidiFile(inputFilename);
    auto trackCount = midiFilePtr->getNumTracks();
    for (auto index = 0; index < trackCount; index++) {
        auto trackPtr = MidiTrack::loadFromMidiFile(midiFilePtr, index, nullptr, &m_midiOutput);
        addTrack(trackPtr);
    }
}

std::unique_ptr<Track> TheLambsSong::loadSamplesTrack(const juce::XmlElement* pPatchesElement, VirtualBand* pVirtualBand)
{
    auto pSampleEngine = pVirtualBand->getSampleEngine();
    auto pAudioFormatManager = pVirtualBand->getAudioFormatManager();
    auto samplesTrackPtr = std::unique_ptr<SamplesTrack>();
    auto pSamplesElement = pPatchesElement->getChildByName("Samples");
    if (pSamplesElement != nullptr) {
        for (auto* pSampleElement : pSamplesElement->getChildWithTagNameIterator("Sample")) {
            auto sampleName = pSampleElement->getStringAttribute("name");
            auto tick = pSampleElement->getIntAttribute("tick");
            auto offset = pSampleElement->getIntAttribute("offset");
            auto sampleEventPtr = std::make_unique<SampleEvent>(pSampleEngine, pAudioFormatManager, sampleName, m_resourcesPath, 0);
            samplesTrackPtr->

        }
    }
    return samplesTrackPtr;
}

TheLambsSong::TheLambsSong(const juce::XmlElement* pPatchesElement, VirtualBand* pVirtualBand)
    :   Song(pPatchesElement->getStringAttribute("name"))
{
    m_resourcesPath = pVirtualBand->getResourcePath();
    auto pMidiDevice = pVirtualBand->getDevice(FractalDeviceType::AxeFxIII);
    auto trackPtr = MidiTrack::loadFromPatchesElement(pPatchesElement, pMidiDevice);
    addTrack(trackPtr);

    m_markerTrackPtr = std::make_unique<MarkerTrack>(pPatchesElement);

    auto pTrackElement = pPatchesElement->getChildByName("Track");
    if (pTrackElement != nullptr) {
        m_trackName = pTrackElement->getStringAttribute("name");
        for (auto* pMarkerElement : pTrackElement->getChildWithTagNameIterator("Marker")) {
            const auto& markerText = pMarkerElement->getAllSubText().trim();

            juce::StringArray tokens;
            tokens.addTokens(markerText, ":", "");
            if (tokens.size() == 3) {
                auto markerPositionInSeconds = tokens[0].getIntValue() * 3600 + tokens[1].getIntValue() * 60 + tokens[2].getIntValue();
                m_backingTrackMarkers.emplace_back((double)markerPositionInSeconds);
            }
        }
    }

    loadSamplesTrack(pPatchesElement, pVirtualBand);
}

void TheLambsSong::activate(juce::AudioFormatManager* pAudioFormatManager, juce::AudioTransportSource* pAudioTransportSource, PlayerComponent* pPlayerComponent)
{
    m_playbackEnginePtr = std::make_unique<PlaybackEngine>(this);
    if (!m_trackName.isEmpty()) {
        auto applicationFolder = juce::File::getCurrentWorkingDirectory();
        auto trackPath = getTrackPath();
        auto file = applicationFolder.getChildFile(trackPath);
        if (file != juce::File{}) {
            auto* pReader = pAudioFormatManager->createReaderFor(file);

            if (pReader != nullptr) {
                auto newSourcePtr = std::make_unique<juce::AudioFormatReaderSource>(pReader, true);
                pAudioTransportSource->setSource(newSourcePtr.get(), 0, nullptr, pReader->sampleRate);
                m_readerSourcePtr.reset(newSourcePtr.release());
                auto duration = pAudioTransportSource->getLengthInSeconds();

                std::vector<double> markers;
                for (auto& markerObj : m_backingTrackMarkers)
                    markers.push_back(markerObj.getPosition());

                pPlayerComponent->setSongInfo((float)duration, !m_backingTrackMarkers.empty(), markers);
            }
        }
    }

    m_playbackEnginePtr->seek(0ull);
}

void TheLambsSong::deactivate()
{
    m_playbackEnginePtr = nullptr;
}

void TheLambsSong::selectProgramChange(int programChangeIndex)
{
    if (m_markerTrackPtr != nullptr) {
        auto clickTimepoint = m_markerTrackPtr->getClickTimepoint(programChangeIndex);
        m_playbackEnginePtr->seek(clickTimepoint);
        m_selectedProgramIndex = programChangeIndex;
    } else {
        DBG("[TheLambsSong::selectProgramChange] Missing MidiTrack pointer");
    }
}

void TheLambsSong::updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent)
{
    if (m_markerTrackPtr != nullptr)
        pProgramChangesComponent->update(m_markerTrackPtr.get());
}

std::tuple<int, int> TheLambsSong::getSelectedProgramInfo() const
{
    auto eventCount = (m_markerTrackPtr != nullptr) ? m_markerTrackPtr->getEventCount() : 0;
    return std::make_tuple(m_selectedProgramIndex, eventCount);
}
