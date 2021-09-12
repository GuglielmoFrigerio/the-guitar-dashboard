/*
  ==============================================================================

    TimeSlider.h
    Created: 10 Sep 2021 6:08:39pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TimeSlider : public juce::Slider 
{
public:
    juce::String getTextFromValue(double 	value) override;


};
