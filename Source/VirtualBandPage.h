/*
  ==============================================================================

    VirtualBandPage.h
    Created: 14 Aug 2021 10:48:50am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include <JuceHeader.h>
#include "Page.h"
#include "VirtualBand.h"

class VirtualBandPage : public Page
{
private:    // fields
    std::unique_ptr<VirtualBand> m_virtualBandPtr;
    juce::TextButton m_loadSongLibraryButton;
    std::unique_ptr<juce::FileChooser> m_chooserPtr;

private:    // implementation
    void loadSongLibrary();

public:     // interface
    VirtualBandPage();

    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualBandPage)

};
