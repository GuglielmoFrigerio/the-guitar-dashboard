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
    virtual ~IPlaybackTarget() {}

    virtual void play(std::int64_t currentClick, std::int64_t previousClick) = 0;
    virtual void seek(std::int64_t currentClick, std::int64_t previousClick) = 0;
};
