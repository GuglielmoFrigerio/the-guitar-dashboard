/*
  ==============================================================================

    IPlayable.h
    Created: 13 Aug 2021 11:31:54am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <cstdint>
#include "TimePoint.h"

class Track;

class IPlayable {
public:
    virtual void play(const TimePoint& timepoint, Track& track) = 0;
    virtual std::int64_t play(std::uint64_t currentTick, std::uint64_t previousTick, Track& track) = 0;

    virtual ~IPlayable()
    {
    }
};
