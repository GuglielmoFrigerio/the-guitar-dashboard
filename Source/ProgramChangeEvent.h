/*
  ==============================================================================

    ProgramChangeEvent.h
    Created: 14 Aug 2021 10:06:59am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "Event.h"
#include "ProgramChange.h"

class ProgramChangeEvent : public Event
{
public:
    ProgramChangeEvent(const juce::XmlElement* pInputElement);

    ProgramChange programChange;

    virtual void play(const TimePoint& timepoint, Track& track) override;

    static std::unique_ptr<Event> parse(juce::XmlElement* pPatchElement);
};
