/*
  ==============================================================================

    Song.h
    Created: 13 Aug 2021 7:45:18am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <tuple>
#include "Track.h"
#include "IPlaybackTarget.h"
#include "MidiOutput.h"
#include "MarkerTrack.h"

class SongListComponent;
class ProgramChangesComponent;
class PlayerComponent;
enum class PlayerState;

class Song : public IPlaybackTarget
{
protected:    // fields
    std::vector<std::unique_ptr<Track>> m_tracks;
    juce::String m_name;
    MidiOutput m_midiOutput;
    std::unique_ptr<MarkerTrack> m_markerTrackPtr;

protected:  // interface
    void    addTrack(std::unique_ptr<Track>& newTrack);

    void play(std::int64_t currentClick, std::int64_t previousClick) override;
    void seek(std::int64_t currentClick, std::int64_t previousClick) override;
    virtual void onTick(std::uint64_t offsetTicks) override {}

public:
    Song(const juce::String& name);
    virtual ~Song() {}


    const juce::String& getName() const {
        return m_name;
    }

    virtual void activate(
        juce::AudioFormatManager* pAudioFormatManager,
        juce::AudioTransportSource* pAudioTransportSource,
        PlayerComponent* pPlayerComponent,
        SongListComponent* pSongListComponent) = 0;

    virtual void deactivate();

    virtual juce::String selectProgramChange(int) { return juce::String(); }
    virtual void updateProgramChangesList(ProgramChangesComponent*) {}
    virtual std::tuple<int, int> getSelectedProgramInfo() const = 0;

    virtual void nextMarker(juce::AudioTransportSource*) {}
    virtual void previousMarker(juce::AudioTransportSource*) {}

    virtual void updateMarkers(double , PlayerComponent*) {}

    virtual void onPlayerStateUpdated(PlayerState) {}

    virtual void updateCurrentClick(PlayerComponent* , ProgramChangesComponent* ) {}

    virtual void rewindPlayback() {}

    virtual bool keyPressed(const juce::KeyPress&) { return false; }
    virtual int getCurrentModifierValue() const { return -1; }
};
