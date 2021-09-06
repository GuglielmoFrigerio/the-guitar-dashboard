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
#include "ProgramChangesComponent.h"

class SongListComponent;

class VirtualBand : public IDeviceHost
{
private:
    std::unique_ptr<SongCollection> m_songCollectionPtr;
    std::vector<std::unique_ptr<FractalDevice>> m_fractalDevices;
    juce::AudioFormatManager m_formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> m_readerSource;
    juce::AudioTransportSource m_transportSource;

public:
    VirtualBand();

    void loadDevices();
    void loadSongLibrary(const juce::File& inputFile);

    virtual MidiDevice* getDevice(FractalDeviceType deviceType) const override;
    void updateSongList(SongListComponent* pSongListComponent);
    void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent);
    void activateSong(int songIndex);
    void selectProgramChange(int programChangeIndex);

    Song* getActiveSong() const;
};
