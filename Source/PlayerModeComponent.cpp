/*
  ==============================================================================

    PlayerModeComponent.cpp
    Created: 18 Dec 2022 5:30:18pm
    Author:  gugli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayerModeComponent.h"

//==============================================================================
PlayerModeComponent::PlayerModeComponent()
{
    addAndMakeVisible(m_backingTrackMode);
    addAndMakeVisible(m_songMode);

    m_backingTrackMode.onClick = [this] { updateToggleState();   };

    m_backingTrackMode.setRadioGroupId(ModeButtons);
    m_songMode.setRadioGroupId(ModeButtons);

    setSize(200, 200);
    
    m_backingTrackMode.setToggleState(true, true);
}

PlayerModeComponent::~PlayerModeComponent()
{
}

void PlayerModeComponent::resized()
{
    m_backingTrackMode.setBounds(20, 20, getWidth() - 30, 20);
    m_songMode.setBounds(20, 50, getWidth() - 30, 20);

}

void PlayerModeComponent::updateToggleState()
{
    Mode = m_backingTrackMode.getToggleState() ? PlayerMode::BackingTrack : PlayerMode::Song;

    if (onModeChange != nullptr)
        onModeChange();
}
