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

std::int64_t Song::play(std::uint64_t currentClick, std::uint64_t previousClick) {
    if (m_tracks.size() > 2) {
        m_tracks[2]->play(currentClick, previousClick);
    }
    //for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it) {
    //    (*it)->play(currentClick, previousClick);
    //}
    return 0;
}

Song::Song(const juce::String& name)
    :   m_name(name)
{
}

void Song::activate(juce::AudioFormatManager* pAudioFormatManager, juce::AudioTransportSource* pAudioTransportSource, PlayerComponent* m_pPlayerComponent)
{
}

void Song::deactivate()
{
}
