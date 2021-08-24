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

class SongCollection {
private:    // fields
    std::vector<std::unique_ptr<Song>>   m_songs;

public:
    static std::unique_ptr<SongCollection> loadFromLibraryElement(const juce::XmlElement* pLibraryElement, const VirtualBand* pVirtualBand);
    void addSong(std::unique_ptr<Song>& newSong);
};
