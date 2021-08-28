/*
  ==============================================================================

    SongCollection.cpp
    Created: 13 Aug 2021 7:46:09am
    Author:  gugli

  ==============================================================================
*/

#include "SongCollection.h"
#include "TheLambsSong.h"
#include "ProgramChangesComponent.h"

std::unique_ptr<SongCollection> SongCollection::loadFromLibraryElement(const juce::XmlElement* pLibraryElement, const VirtualBand* pVirtualBand)
{
    auto songColletionPtr = std::make_unique<SongCollection>();

    for (auto* pPatchesElement : pLibraryElement->getChildWithTagNameIterator("Patches")) {
        std::unique_ptr<Song> newSongPtr = std::make_unique<TheLambsSong>(pPatchesElement, pVirtualBand);
        songColletionPtr->addSong(newSongPtr);
    }

    return songColletionPtr;
}

void SongCollection::addSong(std::unique_ptr<Song>& newSong)
{
    m_songs.push_back(std::move(newSong));
}

void SongCollection::enumerateSongs(std::function<void(const Song* pSong, int index)> callback) const
{
    auto index = 0;
    for (const auto& song : m_songs)
    {
        callback(song.get(), index);
        index++;
    }
}

void SongCollection::activateSong(int songIndex)
{
    if (songIndex < m_songs.size()) {
        if (m_currentSongIndex >= 0 && m_currentSongIndex < m_songs.size())
            m_songs[m_currentSongIndex]->deactivate();
        m_currentSongIndex = songIndex;
        m_songs[m_currentSongIndex]->activate();
    }
    else {
        DBG("activateSong: index (" << songIndex << ")is out of bound. Size is " << m_songs.size());
    }
}

void SongCollection::selectProgramChange(int programChangeIndex)
{
    if (m_currentSongIndex >= -1 && m_currentSongIndex < m_songs.size()) {
        m_songs[m_currentSongIndex]->selectProgramChange(programChangeIndex);
    }
    else {
        DBG("[SongCollection::selectProgramChange] index is out bounds");
    }
}

void SongCollection::updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent)
{
    if (m_currentSongIndex != -1) {
        m_songs[m_currentSongIndex]->updateProgramChangesList(pProgramChangesComponent);
    }
}
