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
    m_pPlayerComponent->onChangePosition = [this](float newPosition) { m_transportSource.setPosition(newPosition); };
    m_pPlayerComponent->onPreviousMarker = [this] { previousMarker(); };
    m_pPlayerComponent->onNextMarker = [this] { nextMarker(); };
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

void VirtualBand::timerCallback()
{
    if (m_devicesLoaded && m_songLibraryFileReady) {
        loadSongCollection("Agosto 2021");
        m_songLibraryFileReady = false;
    }

    if (m_pActiveSong != nullptr) {
        auto position = m_transportSource.getCurrentPosition();
        m_pPlayerComponent->updateTrackPosition(position);
        m_pActiveSong->updateMarkers(position, m_pPlayerComponent);
    }
}

void VirtualBand::toggleStartStop()
{
    m_pPlayerComponent->toggleStartStop();
}

void VirtualBand::stopAndRewind()
{
    m_pPlayerComponent->stopAndRewind();
}

void VirtualBand::changeSongPositionBy(double amount)
{
    if (m_pPlayerComponent->isPlaying()) {
        auto position = m_transportSource.getCurrentPosition();
        auto trackLength = m_transportSource.getLengthInSeconds();
        auto nextPosition = position + amount;

        if (nextPosition < 0.0)
            nextPosition = 0.0;

        if (nextPosition < trackLength) {
            m_transportSource.setPosition(nextPosition);
        }
    }
}

void VirtualBand::nextMarker()
{
    if (m_pActiveSong != nullptr)
        m_pActiveSong->nextMarker(&m_transportSource);
}

void VirtualBand::previousMarker()
{
    if (m_pActiveSong != nullptr)
        m_pActiveSong->previousMarker(&m_transportSource);
}

