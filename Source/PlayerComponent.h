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
#include "TimeSlider.h"
#include "DecibelSlider.h"
#include "PlayerModeComponent.h"

enum class PlayerState {
    Stopped,
    Starting,
    Playing,
    Stopping
};

class PlayerComponent : public juce::Component, private juce::Slider::Listener 
{
private:    // fields
    PlayerButton    m_previousButton;
    PlayerButton    m_stopButton;
    PlayerButton    m_playButton;
    PlayerButton    m_nextButton;
    PlayerState     m_playerState;
    TimeSlider      m_trackPositionSlider;
    bool            m_draggingPosition = false;
    bool            m_previousEnabled = false;
    bool            m_nextEnabled = false;
    DecibelSlider   m_volumeSlider;
    juce::Label     m_decibelLabel;
    PlayerModeComponent m_playerModeComponent;
    juce::Label     m_clickLabel;

private:    // implementation
    void sendStateUpdate(PlayerState playerState);
    void disable();
    void startStateChange(PlayerState newPlayerState);

private:
    void sliderValueChanged(juce::Slider* slider) override;
    void sliderDragStarted(juce::Slider*) override;
    void sliderDragEnded(juce::Slider*) override;

public:
    PlayerComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    std::function<void(PlayerState, PlayerMode)> onPlayerCommand;
    std::function<void(float)> onChangePosition;
    std::function<void()> onNextMarker;
    std::function<void()> onPreviousMarker;
    std::function<void(float)> onChangedGain;
    std::function<void(PlayerMode)> onModeChange;

    void changeState(PlayerState newPlayerState);

    void setSongInfo(float trackDuration, bool hasMarkers, std::vector<double>& markers);
    void updateTrackPosition(float position);
    void toggleStartStop();
    void stopAndRewind();
    bool isPlaying() const {
        return m_playerState == PlayerState::Playing;
    }

    void updateMakerButtons(bool previousEnabled, bool nextEnabled);
    void updateCurrentClick(int currentBeats, int currentClicks);
};