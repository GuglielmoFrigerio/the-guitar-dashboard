/*
  ==============================================================================

    Song.cpp
    Created: 13 Aug 2021 7:45:18am
    Author:  gugli

  ==============================================================================
*/

#include "Song.h"

void Song::addTrack(std::unique_ptr<Track>& newTrack)
{
    m_tracks.emplace_back(std::move(newTrack));
}

void Song::play(std::int64_t currentClick, std::int64_t previousClick) {
    for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it) {
        (*it)->play(currentClick, previousClick);
    }
}

void Song::seek(std::int64_t currentClick, std::int64_t previousClick)
{
    for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it) {
        (*it)->seek(currentClick, previousClick);
    }
}

Song::Song(const juce::String& name)
    :   m_name(name)
{
}

void Song::activate(juce::AudioFormatManager*, juce::AudioTransportSource* , PlayerComponent* )
{
}

void Song::deactivate()
{
}
