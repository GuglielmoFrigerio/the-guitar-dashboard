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
    virtual std::int64_t play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track) = 0;

    virtual ~IPlayable()
    {
    }
};
