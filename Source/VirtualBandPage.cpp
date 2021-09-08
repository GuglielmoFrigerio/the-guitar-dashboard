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
                loadSongLibrary(file);
                auto pPropertiesFile = m_properties.getUserSettings();
                pPropertiesFile->setValue("AxeFx3ConfigurationFile", file.getFullPathName());
            }
        });
}

bool VirtualBandPage::keyPressed(const juce::KeyPress& key, Component* originatingComponent)
{
    auto keyCode = key.getKeyCode();
    switch (keyCode) {
    case 65:
        previousMarker();
        break;

    case 66:
        break;

    case 67:
        nextMarker();
        break;

    }
    return false;
}

void VirtualBandPage::nextMarker()
{
    auto pActiveSong = m_virtualBandPtr->getActiveSong();
    if (pActiveSong != nullptr) {
        auto [selected, count] = pActiveSong->getSelectedProgramInfo();
        if (selected >= 0 && selected < count - 1) {
            m_programChangesComponent.selectProgramChange(selected + 1);
        }
    }
}

void VirtualBandPage::previousMarker()
{
    auto pActiveSong = m_virtualBandPtr->getActiveSong();
    if (pActiveSong != nullptr) {
        auto [selected, count] = pActiveSong->getSelectedProgramInfo();
        if (selected > 0) {
            m_programChangesComponent.selectProgramChange(selected -1);
        }
    }
}

void VirtualBandPage::loadSongLibrary(juce::File& file)
{
    m_virtualBandPtr->loadSongLibrary(file);
    m_virtualBandPtr->updateSongList(&m_songListComponent);
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


VirtualBandPage::VirtualBandPage(juce::ApplicationProperties& properties)
    :   m_loadSongLibraryButton("Load Songs Library"),
        m_properties(properties)
{
    addAndMakeVisible(m_loadSongLibraryButton);
    addAndMakeVisible(m_songListComponent);
    addAndMakeVisible(m_programChangesComponent);
    addAndMakeVisible(m_playerComponent);

    m_virtualBandPtr = std::make_unique<VirtualBand>(&m_playerComponent);
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
}

VirtualBandPage::~VirtualBandPage()
{
    m_virtualBandPtr = nullptr;
    removeKeyListener(this);
    shutdownAudio();
}

void VirtualBandPage::resized()
{
    auto rect = getLocalBounds();
    m_loadSongLibraryButton.setBounds(rect.removeFromTop(24));
    m_songListComponent.setBounds(rect.removeFromTop(rect.getHeight()/2));
    m_playerComponent.setBounds(rect.removeFromBottom(80));
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
