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

class VirtualBand : public IDeviceHost
{
private:
    std::unique_ptr<SongLibrary> m_songLibraryPtr;
    std::unique_ptr<Song> m_currentSongPtr;

public:
    virtual std::shared_ptr<MidiDevice> getMidiDevice(const juce::String& deviceName) override;

    void loadDevices();
    void loadMidiPortInfo(juce::ComboBox& inputCombo, juce::ComboBox& outputCombo);
};
