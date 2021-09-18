/*
  ==============================================================================

    PlayerComponent.cpp
    Created: 2 Sep 2021 2:27:51pm
    Author:  gugli

  ==============================================================================
*/

#include "PlayerComponent.h"


void PlayerComponent::sendStateUpdate(PlayerState playerState)
{
    if (onPlayerCommand != nullptr)
        onPlayerCommand(playerState);
}

void PlayerComponent::disable()
{
    m_previousButton.setEnabled(false);
    m_stopButton.setEnabled(false);
    m_playButton.setEnabled(false);
    m_nextButton.setEnabled(false);
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
    addAndMakeVisible(m_trackPositionSlider);

    m_playButton.onClick = [this] { startStateChange(PlayerState::Starting); };
    m_stopButton.onClick = [this] { startStateChange(PlayerState::Stopping); };

    m_previousButton.onClick = [this] {
        if (onPreviousMarker != nullptr)
            onPreviousMarker();
    };

    m_nextButton.onClick = [this] {
        if (onNextMarker != nullptr)
            onNextMarker();
    };

    m_trackPositionSlider.addListener(this);
    m_trackPositionSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);

    disable();
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

    auto sliderBounds = bounds.removeFromTop(50);
    sliderBounds.reduce(30, 0);
    m_trackPositionSlider.setNewBounds(sliderBounds);

    auto margin = 20;

    auto width = bounds.getWidth();
    auto height = bounds.getHeight();

    m_previousButton.setPosition(0, bounds, margin);
    m_stopButton.setPosition(1, bounds, margin);
    m_playButton.setPosition(2, bounds, margin);
    m_nextButton.setPosition(3, bounds, margin);
}

void PlayerComponent::startStateChange(PlayerState newPlayerState)
{
    if (newPlayerState == PlayerState::Stopping && m_playerState == PlayerState::Stopped) {
        if (onChangePosition != nullptr)
            onChangePosition(.0f);
    }
    else {
        m_stopButton.setEnabled(false);
        m_playButton.setEnabled(false);
        sendStateUpdate(newPlayerState);
    }
}

void PlayerComponent::sliderValueChanged(juce::Slider* slider)
{
}

void PlayerComponent::sliderDragStarted(juce::Slider*)
{
    m_draggingPosition = true;
}

void PlayerComponent::sliderDragEnded(juce::Slider*)
{
    m_draggingPosition = false;
    if (onChangePosition != nullptr) {
        auto value = m_trackPositionSlider.getValue();
        onChangePosition((float)value);
    }
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

        case PlayerState::Playing:
            m_playButton.setEnabled(false);
            m_stopButton.setEnabled(true);
            break;
        }
    }
}

void PlayerComponent::setSongInfo(float trackDuration, bool hasMarkers, std::vector<double>& markers)
{
    m_playerState = PlayerState::Stopped;
    m_trackPositionSlider.setTrackDuration(trackDuration);
    m_playButton.setEnabled(true);

    m_trackPositionSlider.setupMarkers(markers);

    updateMakerButtons(hasMarkers, hasMarkers);
}

void PlayerComponent::updateTrackPosition(float position)
{
    if (!m_draggingPosition)
        m_trackPositionSlider.setValue(position);
}

void PlayerComponent::toggleStartStop()
{
    if (m_playerState == PlayerState::Stopped)
        startStateChange(PlayerState::Starting);
    else if (m_playerState == PlayerState::Playing)
        startStateChange(PlayerState::Stopping);
}

void PlayerComponent::stopAndRewind()
{
    if (m_playerState == PlayerState::Playing) {
        if (onChangePosition != nullptr)
            onChangePosition(.0f);
        startStateChange(PlayerState::Stopping);
    }
    else if (m_playerState == PlayerState::Stopped) {
        if (onChangePosition != nullptr)
            onChangePosition(.0f);
    }
}

void PlayerComponent::updateMakerButtons(bool previousEnabled, bool nextEnabled)
{
    if (previousEnabled != m_previousEnabled) {
        m_previousEnabled = previousEnabled;
        m_previousButton.setEnabled(m_previousEnabled);
    }
    if (nextEnabled != m_nextEnabled) {
        m_nextEnabled = nextEnabled;
        m_nextButton.setEnabled(m_nextEnabled);
    }
}
