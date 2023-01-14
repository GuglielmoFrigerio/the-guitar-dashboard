/*
  ==============================================================================

    AutomationEvent.cpp
    Created: 8 Jan 2023 7:26:45pm
    Author:  gugli

  ==============================================================================
*/

#include "AutomationEvent.h"

void AutomationEvent::play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track)
{
}

void AutomationEvent::seek(std::uint64_t currentClick, std::uint64_t previousClick, Track& track)
{
}

AutomationEvent::AutomationEvent(const juce::String& actionName)
    : m_actionName(actionName)
{
}
