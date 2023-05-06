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
#include "MetronomeTrack.h"
#include "TriplePlayConnect.h"
#include "AutomationTrack.h"
#include "SongListComponent.h"

void TheLambsSong::stopPlayback()
{
    if (m_playbackEnginePtr != nullptr)
        m_playbackEnginePtr->stop();
}

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
    auto pSamplesElement = pPatchesElement->getChildByName("Samples");
    if (pSamplesElement != nullptr) {
        return std::make_unique<SamplesTrack>(pSamplesElement, pVirtualBand);
    }
    return nullptr;
}

void TheLambsSong::onPlayerStateUpdated(PlayerState newPlayerState)
{
    if (m_playbackEnginePtr != nullptr) {
        switch (newPlayerState) {
        case PlayerState::Starting:
            m_playbackEnginePtr->start();
            m_backgroundPlayerStateHandler.starting();
            break;

        case PlayerState::Stopping:
            m_playbackEnginePtr->stop();
            m_backgroundPlayerStateHandler.stopping();
            break;
        }
    }
}

void TheLambsSong::updateCurrentClick(PlayerComponent* pPlayerComponent, ProgramChangesComponent* pProgramChangeComponent)
{
    m_backgroundPlayerStateHandler.timerCallback(
        [pPlayerComponent]() { pPlayerComponent->changeState(PlayerState::Playing); },
        [pPlayerComponent]() { pPlayerComponent->changeState(PlayerState::Stopped); }
    );

    auto currentClick = (int)m_playbackEnginePtr->getClicks();
    auto clicksPerBeat = (int)m_playbackEnginePtr->getClicksPerBeat();
    auto beats = currentClick / clicksPerBeat;
    auto clicks = currentClick % clicksPerBeat;
    pPlayerComponent->updateCurrentClick(beats, clicks);

    if (m_markerTrackPtr != nullptr) {
        auto index = m_markerTrackPtr->getIndexFromClicks(currentClick);
        if (index != m_selectedProgramIndex) {
            pProgramChangeComponent->updateProgramChange(index);
            m_selectedProgramIndex = index;
        }
    }
}

void TheLambsSong::rewindPlayback()
{
    m_playbackEnginePtr->seek(0);
}

void TheLambsSong::onNoteOn(int, int noteNumber, std::uint8_t velocity)
{
    if (noteNumber == m_playOnNote && velocity >= m_minVelocity) {
        m_playbackEnginePtr->start();
        m_backgroundPlayerStateHandler.backgroundStarted();
    }
}

void TheLambsSong::setupMidiRecorder()
{
    if (m_triplePlayConnectPtr != nullptr) {
        m_midiRecorderPtr = std::make_shared<MidiRecorder>();
        m_triplePlayConnectPtr->setMidiInputCallback(m_midiRecorderPtr.get());
    }
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

    auto sampleTrackPtr = loadSamplesTrack(pPatchesElement, pVirtualBand);
    if (sampleTrackPtr != nullptr) {
        addTrack(sampleTrackPtr);
    }

    std::unique_ptr<Track> metronomeTrackPtr = std::make_unique<MetronomeTrack>(pVirtualBand);
    addTrack(metronomeTrackPtr);

    std::unique_ptr<Track> automationTrackPtr = std::make_unique<AutomationTrack>(pPatchesElement, this);
    if (automationTrackPtr->getEventCount() > 0)
        addTrack(automationTrackPtr);

    m_initialBpm = pPatchesElement->getIntAttribute("initialBpm");
}

void TheLambsSong::activate(
    juce::AudioFormatManager* pAudioFormatManager, 
    juce::AudioTransportSource* pAudioTransportSource, 
    PlayerComponent* pPlayerComponent,
    SongListComponent* pSongListComponent)
{
    m_playbackEnginePtr = std::make_unique<PlaybackEngine>(this);
    if (m_initialBpm > 0) {
        m_playbackEnginePtr->setBeatsPerMinute(m_initialBpm);
    }
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

    m_triplePlayConnectPtr = std::make_unique<TriplePlayConnect>(this);
    m_triplePlayConnectPtr->onSongSelect = [pSongListComponent](int songIndex) {
        pSongListComponent->selectSong(songIndex);
    };
}

void TheLambsSong::deactivate()
{
    m_playbackEnginePtr = nullptr;
    m_triplePlayConnectPtr = nullptr;
}

void TheLambsSong::selectProgramChange(int programChangeIndex)
{
    if (m_markerTrackPtr != nullptr) {
        auto& marker = m_markerTrackPtr->getMarker(programChangeIndex);
        auto clickTimepoint = marker.getClickTimepoint();
        m_playbackEnginePtr->seek(clickTimepoint);

        m_playOnNote = marker.getPlayOnNote();
        m_minVelocity = marker.getMinVelocity();
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
    return std::make_tuple(m_selectedProgramIndex, static_cast<int>(eventCount));
}

TheLambsSong::BackgroungPlayerStateHandler::BackgroungPlayerStateHandler()
    : m_currentState(PlayerState::Stopped), m_nextState(PlayerState::Stopped) {
}

void TheLambsSong::BackgroungPlayerStateHandler::timerCallback(std::function<void()> onPlaying, std::function<void()> onStopped)
{
    if (m_currentState != m_nextState) {
        if (m_nextState == PlayerState::Playing)
            onPlaying();
        else {
            onStopped();
        }

        m_currentState = m_nextState;
    }
}

void TheLambsSong::BackgroungPlayerStateHandler::backgroundStarted()
{
    m_nextState = PlayerState::Playing;
}

void TheLambsSong::BackgroungPlayerStateHandler::backgroundStopped()
{
    m_nextState = PlayerState::Stopped;
}

void TheLambsSong::BackgroungPlayerStateHandler::starting()
{
    m_currentState = m_nextState = PlayerState::Playing;
}

void TheLambsSong::BackgroungPlayerStateHandler::stopping()
{
    m_currentState = m_nextState = PlayerState::Stopping;
}
