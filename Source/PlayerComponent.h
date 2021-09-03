/*
  ==============================================================================

    PlayerComponent.h
    Created: 2 Sep 2021 2:27:51pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PlayerComponent : public juce::Component 
{
private:    // fields
    juce::ImageButton   m_playButton;

public:
    PlayerComponent();

    void paint(juce::Graphics&) override;
    void resized() override;
};