/*
  ==============================================================================

    PlaybackEngine.cpp
    Created: 17 Aug 2022 12:31:04pm
    Author:  Guglielmo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaybackEngine.h"

void PlaybackEngine::hiResTimerCallback()
{
    auto nowTicks = juce::Time::getHighResolutionTicks();
    auto deltaTicks = nowTicks - m_lastTicks;
    auto nsTimepoint = deltaTicks * m_nsPerTick;

    if (!m_averageTimespan.add(nsTimepoint)) {
        float average = m_averageTimespan.getAverage();
        DBG("Average timespan in nS: " << average);
    }

    m_lastTicks = nowTicks;
}

PlaybackEngine::PlaybackEngine()
    : m_averageTimespan(1000)
{
    float ticksPerSecond = juce::Time::getHighResolutionTicksPerSecond();
    m_nsPerTick = 1000000000.0 / ticksPerSecond;
}

void PlaybackEngine::start()
{
    m_startTicks = juce::Time::getHighResolutionTicks();
    m_lastTicks = juce::Time::getHighResolutionTicks();
    startTimer(m_timespan);
}

void PlaybackEngine::stop()
{
    stopTimer();
}
