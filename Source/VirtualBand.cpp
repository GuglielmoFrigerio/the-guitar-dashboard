/*
  ==============================================================================

    VirtualBand.cpp
    Created: 14 Aug 2021 10:37:58am
    Author:  gugli

  ==============================================================================
*/

#include "VirtualBand.h"
#include "GuitarDashCommon.h"
#include "SongListComponent.h"
#include "PlayerComponent.h"

void VirtualBand::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &m_transportSource)
    {
        if (m_transportSource.isPlaying())
            m_pPlayerComponent->changeState(PlayerState::Playing);
        else
            m_pPlayerComponent->changeState(PlayerState::Stopped);
    }
}

void VirtualBand::onPlayerStateUpdated(PlayerState newPlayerState)
{
    if (newPlayerState == PlayerState::Starting)
        m_transportSource.start();

    else if (newPlayerState == PlayerState::Stopping)
        m_transportSource.stop();
}

void VirtualBand::loadSongCollection(juce::StringRef collectionName)
{
    juce::XmlDocument configDocument(m_inputFile);

    auto rootElementPtr = configDocument.getDocumentElement();
    auto pLibraryElement = getChildWithAttribute(rootElementPtr.get(), "name", collectionName);
    m_songCollectionPtr = SongCollection::loadFromLibraryElement(pLibraryElement, this);
    m_pSongListComponent->update(m_songCollectionPtr.get());
}

VirtualBand::VirtualBand(PlayerComponent* pPlayerComponent, SongListComponent* pSongListComponent)
    :   m_pPlayerComponent(pPlayerComponent),
        m_pSongListComponent(pSongListComponent),
        m_songLibraryFileReady(false),
        m_devicesLoaded(false)
{
    m_formatManager.registerBasicFormats();
    m_transportSource.addChangeListener(this);
    m_pPlayerComponent->onPlayerCommand = [this](PlayerState playerState) { onPlayerStateUpdated(playerState); };
}

void VirtualBand::loadDevices()
{
    juce::Thread::launch([this]() {
        m_fractalDevices = FractalDevice::loadAvailableDevices();
        m_devicesLoaded = true;
    });
}

void VirtualBand::loadSongLibrary(const juce::File& inputFile)
{
    m_inputFile = inputFile;
    m_songLibraryFileReady = true;
}

MidiDevice* VirtualBand::getDevice(FractalDeviceType deviceType) const
{
    for (auto& fractalDevicePtr : m_fractalDevices)
    {
        auto dt = fractalDevicePtr->getDeviceType();
        if (dt == deviceType)
            return fractalDevicePtr.get();
    }
    return nullptr;
}

void VirtualBand::updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent)
{
    m_songCollectionPtr->updateProgramChangesList(pProgramChangesComponent);
}

void VirtualBand::activateSong(int songIndex)
{
    m_pActiveSong = m_songCollectionPtr->activateSong(songIndex, &m_formatManager, &m_transportSource, m_pPlayerComponent);
}

void VirtualBand::selectProgramChange(int programChangeIndex)
{
    m_songCollectionPtr->selectProgramChange(programChangeIndex);
}

void VirtualBand::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    m_transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void VirtualBand::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    m_transportSource.getNextAudioBlock(bufferToFill);
}

void VirtualBand::play()
{
    m_transportSource.start();
}

void VirtualBand::timerCallback()
{
    if (m_devicesLoaded && m_songLibraryFileReady) {
        loadSongCollection("Agosto 2021");
        m_songLibraryFileReady = false;
    }

    if (m_pActiveSong != nullptr) {
        auto position = m_transportSource.getCurrentPosition();
        m_pPlayerComponent->updateTrackPosition(position);
    }
}

