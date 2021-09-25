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
        brighter += .5f;

    if (shouldDrawButtonAsHighlighted)
        brighter += .3f;

    if (shouldDrawButtonAsDown)
        brighter += .2f;

    if (brighter > .0f)
        color = color.brighter(brighter);

    LookAndFeel_V4::drawButtonBackground(g, button, color, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

    if (toggle) {
        auto bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);
        g.setColour(m_selectedOutlineColor);
        g.drawRoundedRectangle(bounds, 6.0f, 3.0f);
    }
}

juce::Font TilesLookAndFeed::getTextButtonFont(juce::TextButton& button, int buttonHeight)
{
    auto font = LookAndFeel_V4::getTextButtonFont(button, buttonHeight);
    auto typefaceName = font.getTypefaceName();

    return m_tileFont;
}



TilesLookAndFeed::TilesLookAndFeed()
    :   m_tileFont("<Sans-Serif>", 24, juce::Font::plain),
        m_selectedOutlineColor(juce::Colours::white)
{
    m_colors.push_back(juce::Colour(92, 32, 28));
    m_colors.push_back(juce::Colour(87, 73, 27));
    m_colors.push_back(juce::Colour(55, 92, 28));
    m_colors.push_back(juce::Colour(30, 97, 50));
    m_colors.push_back(juce::Colour(13, 39, 43));
    m_colors.push_back(juce::Colour(34, 104, 115));
    m_colors.push_back(juce::Colour(43, 36, 115));
    m_colors.push_back(juce::Colour(63, 31, 99));
    m_colors.push_back(juce::Colour(87, 27, 89));
    m_colors.push_back(juce::Colour(97, 29, 61));
    m_colors.push_back(juce::Colour(110, 33, 33));
}
