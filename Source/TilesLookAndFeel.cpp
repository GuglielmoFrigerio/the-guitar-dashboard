/*
  ==============================================================================

    TilesLookAndFeel.cpp
    Created: 2 Sep 2021 8:57:59am
    Author:  gugli

  ==============================================================================
*/

#include "TilesLookAndFeel.h"

void TilesLookAndFeed::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto idAsString = button.getComponentID();
    auto buttonIndex = idAsString.getIntValue();
    auto colorIndex = buttonIndex % m_colors.size();
    auto toggle = button.getToggleState();


    auto color = m_colors[colorIndex];

    float brighter = .0f;

    if (toggle)
        brighter += .3f;

    if (shouldDrawButtonAsHighlighted)
        brighter += .3f;

    if (shouldDrawButtonAsDown)
        brighter += .2f;

    if (brighter > .0f)
        color = color.brighter(brighter);

    LookAndFeel_V4::drawButtonBackground(g, button, color, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
}

TilesLookAndFeed::TilesLookAndFeed()
{
    m_colors.push_back(juce::Colour(43, 15, 13));
    m_colors.push_back(juce::Colour(43, 36, 13));
    m_colors.push_back(juce::Colour(26, 43, 13));
    m_colors.push_back(juce::Colour(13, 43, 22));
    m_colors.push_back(juce::Colour(13, 39, 43));
    m_colors.push_back(juce::Colour(13, 25, 43));
    m_colors.push_back(juce::Colour(16, 13, 43));
    m_colors.push_back(juce::Colour(27, 13, 43));
    m_colors.push_back(juce::Colour(42, 13, 43));
    m_colors.push_back(juce::Colour(43, 13, 27));
    m_colors.push_back(juce::Colour(43, 13, 13));
}
