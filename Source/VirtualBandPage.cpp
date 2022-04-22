/*
  ==============================================================================

    VirtualBandPage.cpp
    Created: 14 Aug 2021 10:48:50am
    Author:  gugli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VirtualBandPage.h"

void VirtualBandPage::chooseSongLibrary()
{

    m_chooserPtr = std::make_unique<juce::FileChooser>("Select a configuration file",
        juce::File{},
        "*.xml");

    auto chooserFlags = juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectFiles;

    m_chooserPtr->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();

            if (file != juce::File{})
            {
                auto pPropertiesFile = m_properties.getUserSettings();
                pPropertiesFile->setValue("AxeFx3ConfigurationFile", file.getFullPathName());
                //loadSongLibrary(file);
            }
        });
}

bool VirtualBandPage::keyPressed(const juce::KeyPress& key, Component* originatingComponent)
{
    auto keyCode = key.getKeyCode();

    m_trackPlayerKeyManager.keyPressed(keyCode);

    auto it = m_keyHandlerMap.find(keyCode);
    if (it != m_keyHandlerMap.end())
        it->second(key, originatingComponent);

    return true;
}

bool VirtualBandPage::keyStateChanged(bool isKeyDown, Component* originatingComponent)
{
    m_trackPlayerKeyManager.keyStateChanged(isKeyDown);
    return false;
}

void VirtualBandPage::nextProgramChange()
{
    auto pActiveSong = m_virtualBandPtr->getActiveSong();
    if (pActiveSong != nullptr) {
        auto [selected, count] = pActiveSong->getSelectedProgramInfo();
        if (selected >= 0 && selected < count - 1) {
            m_programChangesComponent.selectProgramChange(selected + 1);
        }
    }
}

void VirtualBandPage::previousProgramChange()
{
    auto pActiveSong = m_virtualBandPtr->getActiveSong();
    if (pActiveSong != nullptr) {
        auto [selected, count] = pActiveSong->getSelectedProgramInfo();
        if (selected > 0) {
            m_programChangesComponent.selectProgramChange(selected -1);
        }
    }
}

void VirtualBandPage::nextMarker()
{
    m_virtualBandPtr->nextMarker();
}

void VirtualBandPage::previousMarker()
{
    m_virtualBandPtr->previousMarker();
}

void VirtualBandPage::loadSongLibrary(juce::File& file)
{
    m_virtualBandPtr->loadSongLibrary(file);
}

void VirtualBandPage::onFirstResized()
{
    auto pPropertiesFile = m_properties.getUserSettings();
    auto value = pPropertiesFile->getValue("AxeFx3ConfigurationFile");
    if (value.length() > 0) {
        auto file = juce::File(value);
        loadSongLibrary(file);
    }
}

void VirtualBandPage::releaseResources()
{
}

void VirtualBandPage::timerCallback()
{
    m_virtualBandPtr->timerCallback();
}

void VirtualBandPage::setupKeyHandlers()
{
    m_keyHandlerMap.emplace(65, [this](const juce::KeyPress& key, Component* originatingComponent) {
        previousProgramChange();
    });

    m_keyHandlerMap.emplace(67, [this](const juce::KeyPress& key, Component* originatingComponent) {
        nextProgramChange();
    });

    m_keyHandlerMap.emplace(78, [this](const juce::KeyPress& key, Component* originatingComponent) {
        nextMarker();
    });

    m_keyHandlerMap.emplace(80, [this](const juce::KeyPress& key, Component* originatingComponent) {
        previousMarker();
    });

    m_keyHandlerMap.emplace(juce::KeyPress::rightKey, [this](const juce::KeyPress& key, Component* originatingComponent) {
        auto amount = (key.getModifiers().isShiftDown()) ? 5.0 : 10.0;
        m_virtualBandPtr->changeSongPositionBy(amount);
    });

    m_keyHandlerMap.emplace(juce::KeyPress::leftKey, [this](const juce::KeyPress& key, Component* originatingComponent) {
        auto amount = (key.getModifiers().isShiftDown()) ? -5.0 : -10.0;
        m_virtualBandPtr->changeSongPositionBy(amount);
    });
}


VirtualBandPage::VirtualBandPage(juce::ApplicationProperties& properties)
    :   m_loadSongLibraryButton("Load Songs Library"),
        m_properties(properties),
        m_trackPlayerKeyManager(66, 32)
{
    addAndMakeVisible(m_loadSongLibraryButton);
    addAndMakeVisible(m_songListComponent);
    addAndMakeVisible(m_programChangesComponent);
    addAndMakeVisible(m_playerComponent);
    addAndMakeVisible(m_notificationComponent);

    setupKeyHandlers();

    m_virtualBandPtr = std::make_unique<VirtualBand>(&m_playerComponent, &m_songListComponent);
    m_virtualBandPtr->loadDevices();

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 6 : 0, 6); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(6, 6);
    }

    deviceManager.addChangeListener(this);

    m_songListComponent.onSongSelected = [this](int songIndex) { 
        m_virtualBandPtr->activateSong(songIndex);
        m_virtualBandPtr->updateProgramChangesList(&m_programChangesComponent);
    };
    m_programChangesComponent.onProgramChangeSelected = [this](int programChangeIndex) { m_virtualBandPtr->selectProgramChange(programChangeIndex); };
    m_loadSongLibraryButton.onClick = [this] { chooseSongLibrary(); };

    addKeyListener(this);

    m_trackPlayerKeyManager.onKeyPressed = [this](bool holding) {
        if (holding)
            m_virtualBandPtr->stopAndRewind();
        else m_virtualBandPtr->toggleStartStop();
    };

    startTimer(50);
}

VirtualBandPage::~VirtualBandPage()
{
    shutdownAudio();
    m_virtualBandPtr = nullptr;
    removeKeyListener(this);
}

void VirtualBandPage::resized()
{
    auto rect = getLocalBounds();
    m_loadSongLibraryButton.setBounds(rect.removeFromTop(24));
    m_songListComponent.setBounds(rect.removeFromTop(rect.getHeight()/2));
    m_playerComponent.setBounds(rect.removeFromBottom(160));
    m_notificationComponent.setBounds(rect.removeFromBottom(40));
    m_programChangesComponent.setBounds(rect);

    if (m_firstResize) {
        m_firstResize = false;
        onFirstResized();
    }
}

void VirtualBandPage::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    m_virtualBandPtr->prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void VirtualBandPage::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    m_virtualBandPtr->getNextAudioBlock(bufferToFill);
}

void VirtualBandPage::changeListenerCallback(juce::ChangeBroadcaster*)
{
}
