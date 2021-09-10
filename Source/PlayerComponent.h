/*
  ==============================================================================

    PlayerComponent.h
    Created: 2 Sep 2021 2:27:51pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <functional>
#include <JuceHeader.h>
#include "PlayerButton.h"

enum class PlayerState {
    Stopped,
    Starting,
    Playing,
    Stopping
};

class PlayerComponent : public juce::Component 
{
private:    // fields
    PlayerButton    m_previousButton;
    PlayerButton    m_stopButton;
    PlayerButton    m_playButton;
    PlayerButton    m_nextButton;
    PlayerState     m_playerState;
    juce::Slider    m_trackPositionSlider;

private:    // implementation
    void sendStateUpdate();
    void disable();

public:
    PlayerComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    std::function<void(PlayerState)> onPlayerCommand;
    std::function<void(float)> onChangePosition;

    void changeState(PlayerState newPlayerState);

    void setTrackDuration(float trackDuration);
    void updateTrackPosition(float position);
};