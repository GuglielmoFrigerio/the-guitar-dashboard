/*
  ==============================================================================

    PlaybackEngine.h
    Created: 17 Aug 2022 12:31:04pm
    Author:  Guglielmo

  ==============================================================================
*/

#pragma once
#include "AverageComputer.h"

class PlaybackEngine : public juce::HighResolutionTimer {

private:    // fields
    float           m_nsPerTick = 0.0f;
    std::int64_t    m_startTicks = 0;
    std::int64_t    m_lastTicks = 0;
    int             m_timespan = 2;

    AverageComputer<float> m_averageTimespan;

private:    // implementation
    void hiResTimerCallback() override;

public:
    PlaybackEngine();

    void start();
    void stop();
};
