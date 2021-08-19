/*
  ==============================================================================

    VirtualBand.h
    Created: 14 Aug 2021 10:37:58am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include "SongLibrary.h"
#include "Song.h"
#include "IDeviceHost.h"
#include "FractalDevice.h"

class VirtualBand : public IDeviceHost
{
private:
    std::unique_ptr<SongLibrary> m_songLibraryPtr;
    std::unique_ptr<Song> m_currentSongPtr;
    std::vector<std::unique_ptr<FractalDevice>> m_fractalDevices;

public:
    virtual std::shared_ptr<MidiDevice> getMidiDevice(const juce::String& deviceName) override;
    void loadDevices();
    void teatProgramChange();
};
