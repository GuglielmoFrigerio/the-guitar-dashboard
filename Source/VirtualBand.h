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
class PlayerComponent;
enum class PlayerState;

class VirtualBand : public IDeviceHost, public juce::ChangeListener
{
private:    // fields
    std::unique_ptr<SongCollection> m_songCollectionPtr;
    std::vector<std::unique_ptr<FractalDevice>> m_fractalDevices;
    juce::AudioFormatManager m_formatManager;
    juce::AudioTransportSource m_transportSource;
    PlayerComponent* m_pPlayerComponent;

private:    // implementation
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void onPlayerStateUpdated(PlayerState newPlayerState);

public: // interface
    VirtualBand(PlayerComponent * pPlayerComponent);

    void loadDevices();
    void loadSongLibrary(const juce::File& inputFile);

    virtual MidiDevice* getDevice(FractalDeviceType deviceType) const override;
    void updateSongList(SongListComponent* pSongListComponent);
    void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent);
    void activateSong(int songIndex);
    void selectProgramChange(int programChangeIndex);

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);

    Song* getActiveSong() const;

    void play();
};
