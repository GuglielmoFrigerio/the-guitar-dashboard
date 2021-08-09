/*
  ==============================================================================

    GuitarDashCommon.cpp
    Created: 9 Aug 2021 11:33:52am
    Author:  gugli

  ==============================================================================
*/

#include "GuitarDashCommon.h"

int computeSamplesFromMidiNote(int midiNote, double sampleRate)
{
    auto minimumFrequency = ReferenceFrequency * std::powf(2.0f, ((float)midiNote - 69.0f) / 12.0f);
    return (int)std::round(sampleRate / minimumFrequency);
}

