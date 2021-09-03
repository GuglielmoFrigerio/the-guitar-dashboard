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
#include "PlayerComponent.h"

class VirtualBandPage : public Page, public juce::KeyListener
{
private:    // fields
    std::unique_ptr<VirtualBand> m_virtualBandPtr;
    juce::TextButton m_loadSongLibraryButton;
    std::unique_ptr<juce::FileChooser> m_chooserPtr;
    SongListComponent m_songListComponent;
    ProgramChangesComponent m_programChangesComponent;
    juce::ApplicationProperties& m_properties;
    bool m_firstResize = true;
    PlayerComponent m_playerComponent;

private:    // implementation
    void chooseSongLibrary();
    virtual bool keyPressed(const juce::KeyPress& key, Component* originatingComponent) override;
    void nextMarker();
    void previousMarker();
    void loadSongLibrary(juce::File& file);
    void onFirstResized();

public:     // interface
    VirtualBandPage(juce::ApplicationProperties& properties);
    ~VirtualBandPage() override;

    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualBandPage)

};
