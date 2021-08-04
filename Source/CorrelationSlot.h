/*
  ==============================================================================

    CorrelationSlot.h
    Created: 3 Aug 2021 5:14:55pm
    Author:  gugli

  ==============================================================================
*/

#pragma once

struct CorrelationSlot {
    int     sampleCount;
    float   correlationSum;
    int     midiNote;

    CorrelationSlot(int sampleCount, int midiNote);
};
