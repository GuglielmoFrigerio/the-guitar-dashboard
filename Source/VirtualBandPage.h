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
#include "SongListComponent.h"
#include "ProgramChangesComponent.h"

class VirtualBandPage : public Page, public juce::KeyListener
{
private:    // fields
    std::unique_ptr<VirtualBand> m_virtualBandPtr;
    juce::TextButton m_loadSongLibraryButton;
    std::unique_ptr<juce::FileChooser> m_chooserPtr;
    SongListComponent m_songListComponent;
    ProgramChangesComponent m_programChangesComponent;

private:    // implementation
    void loadSongLibrary();
    virtual bool keyPressed(const juce::KeyPress& key, Component* originatingComponent) override;

public:     // interface
    VirtualBandPage();
    ~VirtualBandPage() override;

    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualBandPage)

};
