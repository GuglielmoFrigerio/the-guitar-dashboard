/*
  ==============================================================================

    Song.h
    Created: 13 Aug 2021 7:45:18am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include "Track.h"

class ProgramChangesComponent;

class Song 
{
protected:    // fields
    std::vector<std::unique_ptr<Track>> m_tracks;
    juce::String m_name;

protected:  // interface
    void    addTrack(std::unique_ptr<Track> newTrack);

public:
    Song(const juce::String& name);

    virtual void nextMarker();
    virtual void previousMarker();

    const juce::String& getName() const {
        return m_name;
    }

    virtual void activate();

    virtual void deactivate();

    virtual void selectProgramChange(int programChangeIndex) {}
    virtual void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent) {}
};
