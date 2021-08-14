/*
  ==============================================================================

    ProgramChangeEvent.cpp
    Created: 14 Aug 2021 10:06:59am
    Author:  gugli

  ==============================================================================
*/

#include "ProgramChangeEvent.h"
#include "Track.h"

void ProgramChangeEvent::play(const TimePoint& timepoint, Track& track)
{
    track.sendProgramChange(*this); 
}
