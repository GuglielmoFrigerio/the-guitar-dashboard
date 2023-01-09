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

class AutomationEvent : public Event {
private:
    std::string m_actionName;

private:    // implementation
    void play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track) override;
    void seek(std::uint64_t currentClick, std::uint64_t previousClick, Track& track) override;

public:
    AutomationEvent(const std::string& actionName);

};
