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
#include "SongListComponent.h"


class Song;
class VirtualBand;
class ProgramChangesComponent;
class PlayerComponent;

class SongCollection {
private:    // fields
    std::vector<std::unique_ptr<Song>>   m_songs;
    int m_currentSongIndex = -1;
    Song* m_pCurrentSong = nullptr;

public:
    static std::unique_ptr<SongCollection> loadFromLibraryElement(const juce::XmlElement* pLibraryElement, VirtualBand* pVirtualBand);
    void addSong(std::unique_ptr<Song>& newSong);

    void enumerateSongs(std::function<void(const Song* pSong, int index)> callback) const;
    Song* activateSong(
        int songIndex, 
        juce::AudioFormatManager* pAudioFormatManager, 
        juce::AudioTransportSource* pAudioTransportSource,
        PlayerComponent* pPlayerComponent,
        SongListComponent* pSongListComponent);

    void selectProgramChange(int programChangeIndex);
    void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent);
};
