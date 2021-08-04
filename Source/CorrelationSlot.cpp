/*
  ==============================================================================

    CorrelationSlot.cpp
    Created: 3 Aug 2021 5:14:55pm
    Author:  gugli

  ==============================================================================
*/

#include <cmath>
#include "CorrelationSlot.h"

CorrelationSlot::CorrelationSlot(int sampleCount, int midiNote)
    :   sampleCount(sampleCount),
        midiNote(midiNote)
{
    correlationSum = NAN;
}
