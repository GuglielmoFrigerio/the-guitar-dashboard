/*
  ==============================================================================

    SongCollection.cpp
    Created: 13 Aug 2021 7:46:09am
    Author:  gugli

  ==============================================================================
*/

#include "SongCollection.h"
#include "TheLambsSong.h"

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

void SongCollection::enumerateSongs(std::function<void(const Song* pSong)> callback)
{
    for (const auto& song : m_songs)
    {
        callback(song.get());
    }
}
