/*
  ==============================================================================

    PlayerComponent.h
    Created: 2 Sep 2021 2:27:51pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PlayerButton.h"

class PlayerComponent : public juce::Component 
{
private:    // fields
    PlayerButton   m_previousButton;
    PlayerButton   m_stopButton;
    PlayerButton   m_playButton;
    PlayerButton   m_nextButton;

public:
    PlayerComponent();

    void paint(juce::Graphics&) override;
    void resized() override;
};