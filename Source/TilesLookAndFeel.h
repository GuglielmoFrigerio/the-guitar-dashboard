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
    int m_colourIndex = 0;

private:    // implementation
    virtual void drawButtonBackground (juce::Graphics& g, juce::Button& button , const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

public:
    TilesLookAndFeed();

};
