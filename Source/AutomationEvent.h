/*
  ==============================================================================

    AutomationEvent.h
    Created: 8 Jan 2023 7:26:45pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Event.h"
#include "IAutomationTarget.h"

class AutomationEvent : public Event {
private:
    using EventHandler = void (AutomationEvent::*)(void);
    EventHandler m_eventHandler;
    IAutomationTarget* m_pAutomationTarget;

private:    // implementation
    void play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track) override;
    void seek(std::uint64_t currentClick, std::uint64_t previousClick, Track& track) override;

    void stopPlayback();

public:
    AutomationEvent(const juce::String& actionName, IAutomationTarget* pAutomationTarget);

};
