/*
  ==============================================================================

    TimeSlider.cpp
    Created: 10 Sep 2021 6:08:39pm
    Author:  gugli

  ==============================================================================
*/

#include "TimeSlider.h"

void TimeSlider::paint(juce::Graphics& g)
{
    juce::Slider::paint(g);
    drawMarker(60.0, g);
}

void TimeSlider::drawMarker(float position, juce::Graphics& g)
{
    if (m_trackDuration > 0.0f) {
        auto xPotion = int((position / m_trackDuration) * m_width);
        g.drawLine(xPotion, 0, xPotion, 20, 2.0f);
    }
}

juce::String TimeSlider::getTextFromValue(double value)
{
    auto totalSeconds = static_cast<int>(value);
    auto minutes = totalSeconds % 60;
    auto seconds = totalSeconds / 60;
    auto fractions = (value - totalSeconds) * 100.0;

    return juce::String::formatted("%2.2d:%2.2d.%2.2d", seconds, minutes, static_cast<int>(fractions));
}

void TimeSlider::setNewBounds(juce::Rectangle<int> r)
{
    m_width = r.getWidth();
    setBounds(r);
}

void TimeSlider::setTrackDuration(float trackDuration)
{
    m_trackDuration = trackDuration;
    setRange(.0f, trackDuration);
}
