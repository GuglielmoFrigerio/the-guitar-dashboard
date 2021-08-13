/*
  ==============================================================================

    IPlayable.h
    Created: 13 Aug 2021 11:31:54am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "TimePoint.h"

class IPlayable {
public:
    virtual void play(const TimePoint& timepoint) = 0;
};
