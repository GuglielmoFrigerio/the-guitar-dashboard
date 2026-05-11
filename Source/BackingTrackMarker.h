/*
  ==============================================================================

    BackingTrackMarker.h
    Created: 26 Aug 2021 2:41:12pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class BackingTrackMarker
{
private:    // fields
    double m_position;

public:
    BackingTrackMarker(double position);

    void activate(juce::AudioTransportSource* pAudioTransportSource);
    double getPosition() const {
        return m_position;
    }
};
