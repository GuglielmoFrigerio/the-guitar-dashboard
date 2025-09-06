/*
  ==============================================================================

    TheLambsSong.h
    Created: 21 Aug 2021 7:04:54pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <tuple>
#include "Song.h"
#include "BackingTrackMarker.h"
#include "PlaybackEngine.h"
#include "MarkerTrack.h"
#include "IMidiInputTarget.h"
#include "TriplePlayConnect.h"
#include "IAutomationTarget.h"
#include "MidiRecorder.h"
#include "SongPatch.h"

class VirtualBand;
class MidiTrack;
class PlayerComponent;

class TheLambsSong : public Song, public IMidiInputTarget, public IAutomationTarget
{
private:    // fields
    int m_selectedProgramIndex = 0;
    std::unique_ptr<juce::AudioFormatReaderSource> m_readerSourcePtr;
    juce::String m_trackName;
    std::vector<BackingTrackMarker> m_backingTrackMarkers;
    const double m_previousGuardTime = 1.0;
    std::unique_ptr<PlaybackEngine> m_playbackEnginePtr;
    std::unique_ptr<MarkerTrack> m_markerTrackPtr;
    juce::String m_resourcesPath;
    int m_initialBpm = 0;
    int m_playOnNote = -1;
    int m_minVelocity = 127;
    std::unique_ptr<TriplePlayConnect> m_triplePlayConnectPtr;
    std::shared_ptr<MidiRecorder> m_midiRecorderPtr;
    std::vector<juce::String> m_patchMessages;
    std::vector<std::shared_ptr<SongPatch>> m_songPatches;
    std::shared_ptr<SongPatch> m_currentPatch = nullptr;
    int m_defaultMidiChannel = 1;

    class BackgroungPlayerStateHandler {
    private:
        PlayerState m_currentState;
        PlayerState m_nextState;

    public:
        BackgroungPlayerStateHandler();

        void timerCallback(std::function<void()> onPlaying, std::function<void()> onStopped);

        void backgroundStarted();

        void backgroundStopped();

        void starting();

        void stopping();

    };

    BackgroungPlayerStateHandler m_backgroundPlayerStateHandler;

private:    // IAutomationTarget interface implementaiton
    void stopPlayback() override;

private:
    void nextMarker(juce::AudioTransportSource* pAudioTransportSource) override;
    void previousMarker(juce::AudioTransportSource* pAudioTransportSource) override;
    void updateMarkers(double position, PlayerComponent* pPlayerComponent) override;
    juce::String getTrackPath();
    void loadMidiTracks();
    std::unique_ptr<Track> loadSamplesTrack(const juce::XmlElement* pPatchesElement, VirtualBand* pVirtualBand);
    void onPlayerStateUpdated(PlayerState  newPlayerState) override;
    void updateCurrentClick(PlayerComponent* pPlayerComponent, ProgramChangesComponent* pProgramChangeComponent) override;
    void rewindPlayback() override;

    void onNoteOn(int channel, int noteNumber, std::uint8_t velocity) override;

    void setupMidiRecorder();
    void stopMidiRecorder();
    void loadPatchMessages(const juce::XmlElement* pPatchesElement);
    void loadPatches(const juce::XmlElement* pSongElement);

public:
    TheLambsSong(const juce::XmlElement* pPatchesElement, VirtualBand* pVirtualBand);
    ~TheLambsSong() override {}

    void activate(
        juce::AudioFormatManager* pAudioFormatManager, 
        juce::AudioTransportSource* pAudioTransportSource, 
        PlayerComponent* pPlayerComponent,
        SongListComponent* pSongListComponent) override;

    void deactivate() override;

    juce::String selectProgramChange(int programChangeIndex) override;
    void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent) override;

    std::tuple<int, int> getSelectedProgramInfo() const override;

    bool keyPressed(const juce::KeyPress& key) override;
};
