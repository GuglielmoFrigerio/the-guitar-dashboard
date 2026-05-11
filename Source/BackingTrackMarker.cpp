/*
  ==============================================================================

    BackingTrackMarker.cpp
    Created: 26 Aug 2021 2:41:12pm
    Author:  gugli

  ==============================================================================
*/

#include "BackingTrackMarker.h"

BackingTrackMarker::BackingTrackMarker(double position)
    :   m_position(position)
{
}

void BackingTrackMarker::activate(juce::AudioTransportSource* pAudioTransportSource)
{
    pAudioTransportSource->setPosition(m_position);
}
