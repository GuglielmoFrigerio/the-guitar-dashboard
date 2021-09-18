/*
  ==============================================================================

    TilesLookAndFeel.h
    Created: 2 Sep 2021 8:57:59am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <JuceHeader.h>

class TilesLookAndFeed : public juce::LookAndFeel_V4 
{
private:    // fields
    std::vector<juce::Colour> m_colors;
    juce::Font m_tileFont;

private:    // implementation
    void drawButtonBackground (juce::Graphics& g, juce::Button& button , const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    juce::Font getTextButtonFont(juce::TextButton& button, int buttonHeight) override;

public:
    TilesLookAndFeed();

};
