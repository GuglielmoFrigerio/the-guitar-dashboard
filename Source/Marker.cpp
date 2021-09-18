/*
  ==============================================================================

    Marker.cpp
    Created: 26 Aug 2021 2:41:12pm
    Author:  gugli

  ==============================================================================
*/

#include "Marker.h"

Marker::Marker(double position)
    :   m_position(position)
{
}

void Marker::activate(juce::AudioTransportSource* pAudioTransportSource)
{
    pAudioTransportSource->setPosition(m_position);
}
