/*
  ==============================================================================

    SongListComponent.h
    Created: 26 Aug 2021 3:17:08pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <functional>
#include <JuceHeader.h>
#include "TilesLookAndFeel.h"

class SongCollection;

//==============================================================================
/*
*/
class SongListComponent  : public juce::Component, public juce::Button::Listener
{
private:    // fields
    juce::OwnedArray<juce::TextButton> m_songTiles;
    TilesLookAndFeed    m_tilesLookAndFeel;

private:    // implementation
    virtual void buttonClicked(juce::Button* pButton) override;

public:
    SongListComponent();
    ~SongListComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void update(const SongCollection* pSongCollection);

    std::function<void(int)> onSongSelected;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SongListComponent)
};
