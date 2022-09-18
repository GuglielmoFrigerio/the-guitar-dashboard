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

    void play(const TimePoint& timepoint, Track& track) override;
    std::int64_t play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track) override;

    static std::unique_ptr<Event> parse(juce::XmlElement* pPatchElement);
};
