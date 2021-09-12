/*
  ==============================================================================

    TimeSlider.cpp
    Created: 10 Sep 2021 6:08:39pm
    Author:  gugli

  ==============================================================================
*/

#include "TimeSlider.h"

juce::String TimeSlider::getTextFromValue(double value)
{
    auto totalSeconds = static_cast<int>(value);
    auto minutes = totalSeconds % 60;
    auto seconds = totalSeconds / 60;
    auto fractions = (value - totalSeconds) * 100.0;

    return juce::String::formatted("%2.2d:%2.2d.%2.2d", seconds, minutes, static_cast<int>(fractions));
}
