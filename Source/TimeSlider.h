/*
  ==============================================================================

    TimeSlider.h
    Created: 10 Sep 2021 6:08:39pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <JuceHeader.h>

class TimeSlider : public juce::Slider 
{
private:    // fields
    int m_width = 0;
    int m_heigth = 0;
    float m_trackDuration = .0f;
    std::vector<double> m_markers;
    const int m_markerTriHeigth = 12;
    const int m_markerTriBase = 6;
    juce::Colour m_markerColor;
    const double m_makerLinehickness = 4.0;

private:
    void paint(juce::Graphics& g) override;
    void drawMarker(float position, juce::Graphics& g);

public:
    TimeSlider();
    juce::String getTextFromValue(double value) override;

    void setNewBounds(juce::Rectangle<int> r);
    void setTrackDuration(float trackDuration);
    void setupMarkers(std::vector<double>& markers);
};
