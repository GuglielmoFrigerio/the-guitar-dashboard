/*
  ==============================================================================

    IPlaybackTarget.h
    Created: 20 Aug 2022 9:27:48pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <cstdint>

class IPlaybackTarget {
public:
    virtual std::int64_t play(std::uint64_t currentClick, std::uint64_t previousClick) = 0;
};
