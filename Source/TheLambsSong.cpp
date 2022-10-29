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
    auto osType = juce::SystemStats::getOperatingSystemType();
    if ((osType & juce::SystemStats::Windows) != 0) {
        auto applicationFolder = juce::File::getCurrentWorkingDirectory();
        //return "./Tracks/" + m_trackName;
        return "../../Resources/Tracks/" + m_trackName;
    }
    auto applicationFolder = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile);
    auto path = applicationFolder.getFullPathName();
    return path + "/../../../../../Resources/Tracks/" + m_trackName;
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

TheLambsSong::TheLambsSong(const juce::XmlElement* pPatchesElement, const VirtualBand* pVirtualBand)
    :   Song(pPatchesElement->getStringAttribute("name"))
{
    auto pMidiDevice = pVirtualBand->getDevice(FractalDeviceType::AxeFxIII);
    auto trackPtr = MidiTrack::loadFromPatchesElement(pPatchesElement, pMidiDevice);
    m_pMidiTrack = dynamic_cast<MidiTrack*>(trackPtr.get());
    addTrack(trackPtr);

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
}

void TheLambsSong::activate(juce::AudioFormatManager* pAudioFormatManager, juce::AudioTransportSource* pAudioTransportSource, PlayerComponent* pPlayerComponent)
{
    m_playbackEnginePtr = std::make_unique<PlaybackEngine>(this);
    m_playbackEnginePtr->start();
    loadMidiTracks();
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
}

void TheLambsSong::deactivate()
{
    m_playbackEnginePtr = nullptr;
}

void TheLambsSong::selectProgramChange(int programChangeIndex)
{
    if (m_pMidiTrack != nullptr) {
        m_pMidiTrack->play(programChangeIndex);
        m_selectedProgramIndex = programChangeIndex;
    } else {
        DBG("[TheLambsSong::selectProgramChange] Missing MidiTrack pointer");
    }
}

void TheLambsSong::updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent)
{
    if (m_pMidiTrack != nullptr)
        pProgramChangesComponent->update(m_pMidiTrack);
}

std::tuple<int, int> TheLambsSong::getSelectedProgramInfo() const
{
    auto eventCount = (m_pMidiTrack != nullptr) ? m_pMidiTrack->getEventCount() : 0;
    return std::make_tuple(m_selectedProgramIndex, eventCount);
}
