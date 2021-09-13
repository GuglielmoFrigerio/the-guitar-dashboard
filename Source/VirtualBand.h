/*
  ==============================================================================

    VirtualBand.h
    Created: 14 Aug 2021 10:37:58am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include <atomic>
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
    SongListComponent* m_pSongListComponent;
    std::atomic<bool> m_devicesLoaded;
    std::atomic<bool> m_songLibraryFileReady;
    juce::File m_inputFile;
    Song* m_pActiveSong;

private:    // implementation
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void onPlayerStateUpdated(PlayerState newPlayerState);
    void loadSongCollection(juce::StringRef collectionName);

public: // interface
    VirtualBand(PlayerComponent * pPlayerComponent, SongListComponent* pSongListComponent);

    void loadDevices();
    void loadSongLibrary(const juce::File& inputFile);

    virtual MidiDevice* getDevice(FractalDeviceType deviceType) const override;
    void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent);
    void activateSong(int songIndex);
    void selectProgramChange(int programChangeIndex);

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);

    Song* getActiveSong() const {
        return m_pActiveSong;
    }

    void timerCallback();

    void toggleStartStop();
    void stopAndRewind();
};
