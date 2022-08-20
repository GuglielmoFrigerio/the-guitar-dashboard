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

class ProgramChangesComponent;
class PlayerComponent;

class Song : public IPlaybackTarget
{
protected:    // fields
    std::vector<std::unique_ptr<Track>> m_tracks;
    juce::String m_name;

protected:  // interface
    void    addTrack(std::unique_ptr<Track> newTrack);

    std::int64_t play(std::uint64_t currentTick, std::uint64_t previousTick) override;

public:
    Song(const juce::String& name);
    virtual ~Song() {}


    const juce::String& getName() const {
        return m_name;
    }

    virtual void activate(juce::AudioFormatManager* pAudioFormatManager, juce::AudioTransportSource* pAudioTransportSource, PlayerComponent* m_pPlayerComponent);

    virtual void deactivate();

    virtual void selectProgramChange(int programChangeIndex) {}
    virtual void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent) {}
    virtual std::tuple<int, int> getSelectedProgramInfo() const = 0;

    virtual void nextMarker(juce::AudioTransportSource*) {}
    virtual void previousMarker(juce::AudioTransportSource*) {}

    virtual void updateMarkers(double position, PlayerComponent* pPlayerComponent) {}
};
