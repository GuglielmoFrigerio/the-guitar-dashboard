/*
  ==============================================================================

    VirtualBand.cpp
    Created: 14 Aug 2021 10:37:58am
    Author:  gugli

  ==============================================================================
*/
#include <cmath>
#include "VirtualBand.h"
#include "GuitarDashCommon.h"
#include "SongListComponent.h"
#include "PlayerComponent.h"
#include "NullMidiDevice.h"

void VirtualBand::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &m_transportSource)
    {
        auto currentPos = m_transportSource.getCurrentPosition();
        auto length = m_transportSource.getLengthInSeconds();
        if (std::fabs(currentPos - length) < 0.05)
            m_transportSource.setPosition(0.0);

        if (m_transportSource.isPlaying())
            m_pPlayerComponent->changeState(PlayerState::Playing);
        else
            m_pPlayerComponent->changeState(PlayerState::Stopped);
    }
}

void VirtualBand::onPlayerStateUpdated(PlayerState newPlayerState, PlayerMode mode)
{
    if (mode == PlayerMode::BackingTrack) {
        if (newPlayerState == PlayerState::Starting)
            m_transportSource.start();

        else if (newPlayerState == PlayerState::Stopping)
            m_transportSource.stop();
    }
    else if (m_pActiveSong != nullptr) {
        m_pActiveSong->onPlayerStateUpdated(newPlayerState);

        auto newState = (newPlayerState == PlayerState::Starting) ? PlayerState::Playing : PlayerState::Stopped;

        m_pPlayerComponent->changeState(newState);

    }
}

void VirtualBand::loadSongCollection(juce::StringRef collectionName)
{
    juce::XmlDocument configDocument(m_inputFile);

    auto rootElementPtr = configDocument.getDocumentElement();
    if (rootElementPtr != nullptr) {
        auto pLibraryElement = getChildWithAttribute(rootElementPtr.get(), "name", collectionName);
        m_songCollectionPtr = SongCollection::loadFromLibraryElement(pLibraryElement, this);
        m_pSongListComponent->update(m_songCollectionPtr.get());
    }
}

juce::String VirtualBand::makeResourcePath()
{
    auto osType = juce::SystemStats::getOperatingSystemType();
    if ((osType & juce::SystemStats::Windows) != 0) {
        return "../../Resources/";
    }
    else {
        auto applicationFolder = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile);
        auto path = applicationFolder.getParentDirectory().getFullPathName();
        return path + "/../../../../Resources/";
    }
}

VirtualBand::VirtualBand(PlayerComponent* pPlayerComponent, SongListComponent* pSongListComponent, ProgramChangesComponent* pProgramChangeComponent)
    :   m_pPlayerComponent(pPlayerComponent),
        m_pSongListComponent(pSongListComponent),
        m_pProgramChangeComponent(pProgramChangeComponent),
        m_songLibraryFileReady(false),
        m_devicesLoaded(false),
        m_sampleEngine(makeResourcePath()),
        m_resourcesPath(makeResourcePath())
{
    m_formatManager.registerBasicFormats();
    m_transportSource.addChangeListener(this);
    m_pPlayerComponent->onPlayerCommand = [this](PlayerState playerState, PlayerMode mode) { onPlayerStateUpdated(playerState, mode); };
    m_pPlayerComponent->onChangePosition = [this](float newPosition) { 
        m_transportSource.setPosition(newPosition); 
        if (m_pActiveSong != nullptr && newPosition == 0.0 && m_currentPlayerMode == PlayerMode::Song) {
            m_pActiveSong->rewindPlayback();
        }
    };
    m_pPlayerComponent->onChangedGain = [this](float newGain) { m_transportSource.setGain(newGain); };
    m_pPlayerComponent->onPreviousMarker = [this] { previousMarker(); };
    m_pPlayerComponent->onNextMarker = [this] { nextMarker(); };
    m_pPlayerComponent->onModeChange = [this](PlayerMode newPlayerMode) { m_currentPlayerMode = newPlayerMode; };
    m_currentPlayerMode = PlayerMode::Song;

    m_nullMidiDevice = std::make_unique<NullMidiDevice>();
}

void VirtualBand::loadDevices()
{
    FractalDevice::loadDevicesInfo();
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
    return m_nullMidiDevice.get();
}

void VirtualBand::updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent)
{
    m_songCollectionPtr->updateProgramChangesList(pProgramChangesComponent);
}

void VirtualBand::activateSong(int songIndex)
{
    m_pActiveSong = m_songCollectionPtr->activateSong(songIndex, &m_formatManager, &m_transportSource, m_pPlayerComponent, m_pSongListComponent);
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
    m_sampleEngine.getNextAudioBlock(bufferToFill);
}

void VirtualBand::timerCallback()
{
    if (m_devicesLoaded && m_songLibraryFileReady) {
        m_songLibraryFileReady = false;
        loadSongCollection("Default Library");
    }

    if (m_pActiveSong != nullptr) {
        if (m_currentPlayerMode == PlayerMode::BackingTrack) {
            auto position = m_transportSource.getCurrentPosition();
            m_pPlayerComponent->updateTrackPosition(position);
            m_pActiveSong->updateMarkers(position, m_pPlayerComponent);
        }
        else {
            m_pActiveSong->updateCurrentClick(m_pPlayerComponent, m_pProgramChangeComponent);
        }
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
    auto position = m_transportSource.getCurrentPosition();
    auto trackLength = m_transportSource.getLengthInSeconds();
    auto nextPosition = position + amount;

    if (nextPosition < 0.0)
        nextPosition = 0.0;

    if (nextPosition < trackLength) {
        m_transportSource.setPosition(nextPosition);
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

