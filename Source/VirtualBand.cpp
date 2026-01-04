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
#include "MidiRecorder.h"

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

    if (newPlayerState == PlayerState::Starting) {
        juce::String folderName = m_pActiveSong != nullptr ? m_pActiveSong->getName() : "default";
        m_audioRecorder.startRecording(folderName);
    }
    else if (newPlayerState == PlayerState::Stopping) {
        m_audioRecorder.stop();
    }
    m_sampleEngine.stopAll();
}

void VirtualBand::loadConfig()
{
    auto resourceRoot = juce::File::getCurrentWorkingDirectory().getChildFile(m_resourcesPath);
    juce::File file{ resourceRoot.getParentDirectory().getChildFile("Configuration/Complete.xml")};
    auto ptr = std::make_unique<juce::XmlDocument>(file);
    m_configElementPtr = ptr->getDocumentElement();
}


void VirtualBand::finished (juce::URL::DownloadTask *task, bool) {
    
}

void VirtualBand::progress (juce::URL::DownloadTask *task, juce::int64 bytesDownloaded, juce::int64 totalLength) {
    DBG("bytesDownloaded: " << bytesDownloaded << " totalLength: " << totalLength);
}

void VirtualBand::downloadTest() {
    
    juce::URL testUrl("https://www.google.com");
    auto content = testUrl.readEntireTextStream();
    
    juce::URL binaryUrl("https://link.testfile.org/PDF20MB");
    
    auto inputStream = binaryUrl.createInputStream(juce::URL::InputStreamOptions (juce::URL::ParameterHandling::inAddress));
    
    juce::WebInputStream* pWebInputStream = dynamic_cast<juce::WebInputStream*>(inputStream.get());
    if (pWebInputStream != nullptr){
        char buffer[256];
        auto readCount = pWebInputStream->InputStream::read(buffer, sizeof(buffer));
        DBG(readCount);
    }
    
    auto appGroup = "group.guitarAppGroup";
    //juce::File downloadDestination = juce::File::getContainerForSecurityApplicationGroupIdentifier(appGroup);
    juce::File downloadDestination;
    juce::File f = downloadDestination.getChildFile("archive.zip");
    
    auto exists = f.existsAsFile();
    if (exists)
        f.deleteFile();
    
    auto dnlOpts = juce::URL::DownloadTaskOptions()
        .withSharedContainer(appGroup)
        .withListener(this);

    juce::URL download("https://link.testfile.org/PDF20MB");

    auto downloadTask = download.downloadToFile(f, dnlOpts);
}

void VirtualBand::sendBoxTest() {
    juce::File f(juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).getFullPathName() + juce::File::getSeparatorString() + "sandbox-example.txt");
    
    auto exists = f.existsAsFile();
    
    if (!exists) {
        if (f.create().ok()) {
            f.replaceWithText("Here comes the flood");
            juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon, "Created", "File sandbox-example.txt has been created");
        }
    } else {
        auto content = f.loadFileAsString();
        DBG("File sandbox-example.txt already exists. Content: " << content);
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon, "Read", content);
    }
}

void VirtualBand::loadSongCollection(juce::StringRef collectionName)
{
    if (m_configElementPtr != nullptr) {

        if (m_pActiveSong != nullptr) {
            m_transportSource.setSource(nullptr);
            m_pActiveSong->deactivate();
        }

        auto pLibraryElement = getChildWithAttribute(m_configElementPtr.get(), "name", collectionName);
        m_songCollectionPtr = SongCollection::loadFromLibraryElement(pLibraryElement, this);
        m_pSongListComponent->update(m_songCollectionPtr.get());
    }
}

juce::String VirtualBand::loadLibraries()
{
    m_librariesComboBox.clear();
    juce::String defaultLibraryName;

    m_librariesComboBox.onChange = [this] {
        auto id = m_librariesComboBox.getSelectedId();
        auto libraryName = m_librariesComboBox.getItemText(id - 1);
        loadSongCollection(libraryName);
    };

    auto index = 1;
    if (m_configElementPtr != nullptr) {
        enumChildElements(m_configElementPtr.get(), "Library", [this, &index, &defaultLibraryName](const juce::XmlElement* pChildElement) {
            auto value = pChildElement->getStringAttribute("name");
            if (index == 1)
                defaultLibraryName = value;
            m_librariesComboBox.addItem(value, index++);
        });
    }

    m_librariesComboBox.setSelectedId(1, juce::sendNotification);

    return defaultLibraryName;
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

VirtualBand::VirtualBand(PlayerComponent* pPlayerComponent, SongListComponent* pSongListComponent, ProgramChangesComponent* pProgramChangeComponent, juce::ComboBox& librariesComboBox, juce::AudioDeviceManager& deviceManager)
    :   m_pPlayerComponent(pPlayerComponent),
        m_pSongListComponent(pSongListComponent),
        m_pProgramChangeComponent(pProgramChangeComponent),
        m_songLibraryFileReady(false),
        m_devicesLoaded(false),
        m_sampleEngine(makeResourcePath()),
        m_resourcesPath(makeResourcePath()),
        m_librariesComboBox(librariesComboBox),
        m_audioRecorder(getResourcePath())
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

    deviceManager.addAudioCallback(&m_audioRecorder);
    
    loadConfig();
    
    //downloadTest();
}

void VirtualBand::loadDevices()
{
    m_fractalDevices = FractalDevice::loadAvailableDevices();
    m_devicesLoaded = true;
}

void VirtualBand::loadSongLibrary()
{
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

juce::String VirtualBand::selectProgramChange(int programChangeIndex)
{
    return m_songCollectionPtr->selectProgramChange(programChangeIndex);
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
        loadLibraries();
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

bool VirtualBand::keyPressed(const juce::KeyPress& key) 
{
    if (m_pActiveSong != nullptr)
        return m_pActiveSong->keyPressed(key);
    
    return false;
}

