/*
  ==============================================================================

    VirtualBandPage.cpp
    Created: 14 Aug 2021 10:48:50am
    Author:  gugli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VirtualBandPage.h"

void VirtualBandPage::loadSongLibrary()
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
                m_virtualBandPtr->loadSongLibrary(file);
                m_virtualBandPtr->updateSongList(&m_songListComponent);
            }
        });
}

VirtualBandPage::VirtualBandPage()
    :   m_loadSongLibraryButton("Load Songs Library")
{
    addAndMakeVisible(m_loadSongLibraryButton);
    addAndMakeVisible(m_songListComponent);

    m_loadSongLibraryButton.onClick = [this] { loadSongLibrary(); };

    m_virtualBandPtr = std::make_unique<VirtualBand>();
    m_virtualBandPtr->loadDevices();
}

void VirtualBandPage::resized()
{
    auto rect = getLocalBounds();
    m_loadSongLibraryButton.setBounds(rect.removeFromTop(24));
    m_songListComponent.setBounds(rect);
}
