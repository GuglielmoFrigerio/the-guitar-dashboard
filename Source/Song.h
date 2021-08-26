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

class Song 
{
private:    // fields
    std::vector<std::unique_ptr<Track>> m_tracks;
    juce::String m_name;

protected:  // interface
    void    addTrack(std::unique_ptr<Track> newTrack);

public:
    Song(const juce::String& name);

    virtual void nextMarker();
    virtual void previousMarker();
};
