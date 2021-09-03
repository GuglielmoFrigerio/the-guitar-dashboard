/*
  ==============================================================================

    PlayerButton.cpp
    Created: 3 Sep 2021 4:08:23pm
    Author:  gugli

  ==============================================================================
*/

#include "PlayerButton.h"

PlayerButton::PlayerButton(juce::StringRef imageName)
{
    auto currentDir = juce::File::getCurrentWorkingDirectory();
    auto file = currentDir.getChildFile("../../Resources/Images/" + imageName + ".png");
    auto playerImage = juce::ImageCache::getFromFile(file);
    m_imageWidth = playerImage.getWidth();
    m_imageHeight = playerImage.getHeight();

    setImages(false, true, true,
        playerImage, 1.0f, juce::Colour::fromRGBA(0, 0, 0, 0.0f),
        playerImage, 0.8f, juce::Colour::fromRGBA(0, 0, 0, 0.0f),
        playerImage, 0.6f, juce::Colour::fromRGBA(0, 0, 0, 0.0f),
        0.0f);
}

void PlayerButton::setPosition(int positionIndex, int width, int height, int margin)
{
    auto startX = width / 2 - (m_imageWidth * 2 + margin * 1.5f);
    auto deltaX = m_imageWidth + margin;
    setBounds(startX + deltaX * positionIndex, (height - m_imageHeight) / 2, m_imageWidth, m_imageHeight);
}
