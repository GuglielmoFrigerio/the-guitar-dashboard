/*
  ==============================================================================

    Song.cpp
    Created: 13 Aug 2021 7:45:18am
    Author:  gugli

  ==============================================================================
*/

#include "Song.h"

void Song::addTrack(std::unique_ptr<Track> newTrack)
{
    m_tracks.emplace_back(std::move(newTrack));
}

Song::Song(const juce::String& name)
    :   m_name(name)
{
}

void Song::nextMarker()
{
}

void Song::previousMarker()
{
}
