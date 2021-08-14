/*
  ==============================================================================

    ProgramChangeEvent.h
    Created: 14 Aug 2021 10:06:59am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "Event.h"
#include "ProgramChange.h"

class ProgramChangeEvent : Event
{
public:
    ProgramChange programChange;

    virtual void play(const TimePoint& timepoint, Track& track) override;

};
