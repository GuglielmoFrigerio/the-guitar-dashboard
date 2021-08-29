/*
  ==============================================================================

    SongCollection.h
    Created: 13 Aug 2021 7:46:09am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <memory>
#include <JuceHeader.h>

class Song;
class VirtualBand;
class ProgramChangesComponent;

class SongCollection {
private:    // fields
    std::vector<std::unique_ptr<Song>>   m_songs;
    int m_currentSongIndex = -1;

public:
    static std::unique_ptr<SongCollection> loadFromLibraryElement(const juce::XmlElement* pLibraryElement, const VirtualBand* pVirtualBand);
    void addSong(std::unique_ptr<Song>& newSong);

    void enumerateSongs(std::function<void(const Song* pSong, int index)> callback) const;
    void activateSong(int songIndex);
    void selectProgramChange(int programChangeIndex);
    void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent);

    Song* getActiveSong() const {
        if (m_currentSongIndex >= 0 && m_currentSongIndex < m_songs.size())
            return m_songs[m_currentSongIndex].get();
        DBG("SongCollection::getActiveSong m_currentSongIndex is out of bounds");
        return nullptr;
    }
};
