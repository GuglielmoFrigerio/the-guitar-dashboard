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
    auto state = m_currentState.load();
    auto statePtr = m_stateHandlers[(int)state];
    (this->*statePtr)();
}

PlaybackEngine::PlaybackEngine(IPlaybackTarget* pPlaybackTarget, int beatsPerMinute, int clicksPerBeat)
    : m_pPlaybackTarget(pPlaybackTarget), m_stopOffsetTicks(0), m_currentState(State::Stopped)
{
    m_clicksPerBeat = (double)clicksPerBeat;
    m_ticksPerSecond = (double) juce::Time::getHighResolutionTicksPerSecond();
    setBeatsPerMinute(beatsPerMinute);
    startTimer(m_timespan);
    m_stateHandlers[(int)State::Stopped] = &PlaybackEngine::stoppedHandler;
    m_stateHandlers[(int)State::Starting] = &PlaybackEngine::startingHandler;
    m_stateHandlers[(int)State::Started] = &PlaybackEngine::startedHandler;
    m_stateHandlers[(int)State::Stopping] = &PlaybackEngine::stoppingHandler;
}

PlaybackEngine::~PlaybackEngine()
{
    stopTimer();
}

void PlaybackEngine::start()
{
    if (m_currentState == State::Stopped) {
        m_currentState.store(State::Starting);
    }
}

void PlaybackEngine::stop()
{
    if (m_currentState == State::Started) {
        m_currentState.store(State::Stopping);
    }
}

void PlaybackEngine::setBeatsPerMinute(int beatsPerMinute)
{
    m_beatsPerMinute = beatsPerMinute;
    m_ticksVsClicks.store((m_ticksPerSecond * 60.0) / (m_beatsPerMinute * m_clicksPerBeat));
}

void PlaybackEngine::seek(std::uint64_t clickPosition)
{
    double tickOffset = clickPosition * m_ticksVsClicks.load();
    m_startTicks = juce::Time::getHighResolutionTicks() - (std::uint64_t)round(tickOffset);
}

void PlaybackEngine::stoppedHandler()
{

}

void PlaybackEngine::startingHandler()
{
    m_startTicks = juce::Time::getHighResolutionTicks() - m_stopOffsetTicks;
    m_currentState.store(State::Started);
}

void PlaybackEngine::startedHandler()
{
    auto nowTicks = juce::Time::getHighResolutionTicks();
    auto offsetTicks = nowTicks - m_startTicks;
    auto currentClickDbl = (double)offsetTicks / m_ticksVsClicks.load();
    std::uint64_t currentClick = (std::uint64_t)round(currentClickDbl);
    m_pPlaybackTarget->play(currentClick, m_previousClick);
    m_previousClick = currentClick;
}

void PlaybackEngine::stoppingHandler()
{
    auto nowTicks = juce::Time::getHighResolutionTicks();
    m_stopOffsetTicks = nowTicks - m_startTicks;
    m_currentState.store(State::Stopped);
}
