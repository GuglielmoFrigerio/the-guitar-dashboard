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
    auto offsetTicks = nowTicks - m_startTicks;
    auto currentClickDbl = (double)offsetTicks / m_ticksVsClicks.load();
    std::uint64_t currentClick = (std::uint64_t)round(currentClickDbl);
    m_pPlaybackTarget->play(currentClick, m_previousClick);
    m_previousClick = currentClick;
}

PlaybackEngine::PlaybackEngine(IPlaybackTarget* pPlaybackTarget, int beatsPerMinute, int clicksPerBeat)
    : m_pPlaybackTarget(pPlaybackTarget)
{
    m_clicksPerBeat = (double)clicksPerBeat;
    m_ticksPerSecond = (double) juce::Time::getHighResolutionTicksPerSecond();
    setBeatsPerMinute(beatsPerMinute);
}

void PlaybackEngine::start()
{
    m_startTicks = juce::Time::getHighResolutionTicks();
    startTimer(m_timespan);
}

void PlaybackEngine::stop()
{
    stopTimer();
}

void PlaybackEngine::setBeatsPerMinute(int beatsPerMinute)
{
    m_beatsPerMinute = beatsPerMinute;
    m_ticksVsClicks.store((m_ticksPerSecond * 60.0) / (m_beatsPerMinute * m_clicksPerBeat));
}
