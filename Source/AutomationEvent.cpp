/*
  ==============================================================================

    AutomationEvent.cpp
    Created: 8 Jan 2023 7:26:45pm
    Author:  gugli

  ==============================================================================
*/

#include "GuitarDashCommon.h"
#include "AutomationEvent.h"

void AutomationEvent::play(std::uint64_t, std::uint64_t, Track&)
{
    (this->*m_eventHandler)();
}

void AutomationEvent::seek(std::uint64_t, std::uint64_t, Track&)
{
    (this->*m_eventHandler)();
}

void AutomationEvent::stopPlayback()
{
    m_pAutomationTarget->stopPlayback();
}

AutomationEvent::AutomationEvent(const juce::String& actionName, IAutomationTarget* pAutomationTarget)
    : m_pAutomationTarget(pAutomationTarget)
{
    if (actionName == "stop")
        m_eventHandler = &AutomationEvent::stopPlayback;
    else {
        juce::String message;
        message << "Unknown action '" << actionName << "'";
        throw exceptionFactory(message);
    }
}
