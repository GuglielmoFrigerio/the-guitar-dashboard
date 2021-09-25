/*
  ==============================================================================

    PlayerButton.h
    Created: 3 Sep 2021 4:08:23pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PlayerButton : public juce::ImageButton
{
private:
    int     m_imageWidth;
    int     m_imageHeight;

public:
    PlayerButton(juce::StringRef imageName);
    PlayerButton(const char* imageData, int imageDataLength);

    void setPosition(int positionIndex, juce::Rectangle<int>& rect, int margin);

};
