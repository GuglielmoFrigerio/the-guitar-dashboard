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
private:    // fields
    int m_width = 0;
    float m_trackDuration = .0f;

private:
    void paint(juce::Graphics& g) override;
    void drawMarker(float position, juce::Graphics& g);

public:
    juce::String getTextFromValue(double value) override;

    void setNewBounds(juce::Rectangle<int> r);
    void setTrackDuration(float trackDuration);
};
