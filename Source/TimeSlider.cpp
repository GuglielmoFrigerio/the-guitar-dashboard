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
    if (m_trackDuration > 0.0f) {
        g.setColour(m_markerColor);
        for (auto marker : m_markers)
            drawMarker(marker, g);
    }
}

void TimeSlider::drawMarker(float position, juce::Graphics& g)
{
    auto xPotion = int((position / m_trackDuration) * m_width);
    g.drawLine(xPotion - m_markerTriBase, m_heigth, xPotion, m_heigth - m_markerTriHeigth, m_makerLinehickness);
    g.drawLine(xPotion, m_heigth - m_markerTriHeigth, xPotion + m_markerTriBase, m_heigth, m_makerLinehickness);
    g.drawLine(xPotion + m_markerTriBase, m_heigth, xPotion - m_markerTriBase, m_heigth, m_makerLinehickness);
}

TimeSlider::TimeSlider()
    :   m_markerColor(juce::Colours::yellow)
{
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
    m_heigth = r.getHeight();
    setBounds(r);
}

void TimeSlider::setTrackDuration(float trackDuration)
{
    m_trackDuration = trackDuration;
    setRange(.0f, trackDuration);
}

void TimeSlider::setupMarkers(std::vector<double>& markers)
{
    m_markers.clear();
    for (auto marker : markers)
        m_markers.push_back(marker);
}
