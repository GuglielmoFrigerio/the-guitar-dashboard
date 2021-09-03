/*
  ==============================================================================

    PlayerComponent.cpp
    Created: 2 Sep 2021 2:27:51pm
    Author:  gugli

  ==============================================================================
*/

#include "PlayerComponent.h"

PlayerComponent::PlayerComponent()
{
    auto currentDir = juce::File::getCurrentWorkingDirectory();
    auto file = currentDir.getChildFile("../../Resources/Images/play-button.png");
    auto playImage = juce::ImageCache::getFromFile(file);

    addAndMakeVisible(m_playButton);

    m_playButton.setImages(false, true, true,
        playImage, 1.0f, juce::Colour(0, 0, 0),
        playImage, 1.0f, juce::Colour(0, 0, 0),
        playImage, 1.0f, juce::Colour(0, 0, 0),
        1.0f);
}

void PlayerComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("PlayerComponent", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
}

void PlayerComponent::resized()
{
    auto bounds = getLocalBounds();
    m_playButton.setBounds(bounds);
}
