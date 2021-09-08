/*
  ==============================================================================

    PlayerComponent.cpp
    Created: 2 Sep 2021 2:27:51pm
    Author:  gugli

  ==============================================================================
*/

#include "PlayerComponent.h"


void PlayerComponent::sendStateUpdate()
{
    if (onPlayerCommand != nullptr)
        onPlayerCommand(m_playerState);
}

PlayerComponent::PlayerComponent()
    :   m_playButton("play"),
        m_previousButton("backward"),
        m_nextButton("forward"),
        m_stopButton("stop"),
        m_playerState(PlayerState::Stopped)
{
    addAndMakeVisible(m_playButton);
    addAndMakeVisible(m_previousButton);
    addAndMakeVisible(m_nextButton);
    addAndMakeVisible(m_stopButton);

    m_playButton.onClick = [this] { changeState(PlayerState::Starting); };
    m_stopButton.onClick = [this] { changeState(PlayerState::Stopping); };
}

void PlayerComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}

void PlayerComponent::resized()
{
    auto bounds = getLocalBounds();
    auto margin = 20;

    auto width = bounds.getWidth();
    auto height = bounds.getHeight();

    m_previousButton.setPosition(0, width, height, margin);
    m_stopButton.setPosition(1, width, height, margin);
    m_playButton.setPosition(2, width, height, margin);
    m_nextButton.setPosition(3, width, height, margin);
}

void PlayerComponent::changeState(PlayerState newPlayerState)
{
    if (newPlayerState != m_playerState) {
        m_playerState = newPlayerState;

        switch (newPlayerState)
        {
        case PlayerState::Stopped:
            m_stopButton.setEnabled(true);
            m_playButton.setEnabled(true);
            break;

        case PlayerState::Starting:
            m_playButton.setEnabled(false);
            sendStateUpdate();
            break;

        case PlayerState::Playing:
            m_playButton.setEnabled(true);
            break;

        case PlayerState::Stopping:
            sendStateUpdate();
        }
    }
}
