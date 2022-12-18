/*
  ==============================================================================

    PlayerModeComponent.h
    Created: 18 Dec 2022 5:30:18pm
    Author:  gugli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

enum class PlayerMode {
    BackingTrack,
    Song
};

//==============================================================================
/*
*/
class PlayerModeComponent  : public juce::Component
{
private:    // fields
    juce::ToggleButton m_backingTrackMode { "Backing track" };
    juce::ToggleButton m_songMode{ "Song" };

    enum RadioButtonIds
    {
        ModeButtons = 1001
    };

    void updateToggleState();

public:
    PlayerModeComponent();
    ~PlayerModeComponent() override;

    void resized() override;

    PlayerMode Mode = PlayerMode::BackingTrack;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerModeComponent)
};
