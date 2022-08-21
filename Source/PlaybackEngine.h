/*
  ==============================================================================

    PlaybackEngine.h
    Created: 17 Aug 2022 12:31:04pm
    Author:  Guglielmo

  ==============================================================================
*/

#pragma once
#include <atomic>
#include "AverageComputer.h"
#include "IPlaybackTarget.h"

class PlaybackEngine : public juce::HighResolutionTimer {

private:    // fields
    double                  m_ticksPerSecond = 0.0;
    std::int64_t            m_startTicks = 0;
    int                     m_timespan = 1;
    double                  m_beatsPerMinute = 120.0;
    double                  m_clicksPerBeat = 480.0;
    std::atomic<double>     m_ticksVsClicks = 0.0;
    IPlaybackTarget*        m_pPlaybackTarget = nullptr;
    std::uint64_t           m_previousClick = 0;

private:    // implementation
    void hiResTimerCallback() override;

public:
    PlaybackEngine(IPlaybackTarget* pPlaybackTarget, int beatsPerMinute = 120, int clicksPerBeat = 480);

    void start();
    void stop();
    void setBeatsPerMinute(int beatsPerSecond);
};
