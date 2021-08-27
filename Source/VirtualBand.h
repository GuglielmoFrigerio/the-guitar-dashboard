/*
  ==============================================================================

    VirtualBand.h
    Created: 14 Aug 2021 10:37:58am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include "SongCollection.h"
#include "Song.h"
#include "IDeviceHost.h"
#include "FractalDevice.h"

class SongListComponent;

class VirtualBand : public IDeviceHost
{
private:
    std::unique_ptr<SongCollection> m_songCollectionPtr;
    std::vector<std::unique_ptr<FractalDevice>> m_fractalDevices;

public:
    void loadDevices();
    void loadSongLibrary(const juce::File& inputFile);

    virtual MidiDevice* getDevice(FractalDeviceType deviceType) const override;
    void updateSongList(SongListComponent* pSongListComponent);
    void activateSong(int songIndex);
    void selectProgramChange(int programChangeIndex);
};
