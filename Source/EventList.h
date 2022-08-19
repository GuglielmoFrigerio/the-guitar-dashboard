/*
  ==============================================================================

    EventList.h
    Created: 13 Aug 2021 11:30:45am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "IPlayable.h"
#include "Event.h"

class EventList : public IPlayable
{
private:    // fields
    std::vector<std::unique_ptr<Event>> m_events;
    std::uint64_t m_clicktimepoint;

public:     // interface
    EventList(std::unique_ptr<Event>& firstEvent);
    virtual void play(const TimePoint& timepoint, Track& track) override;
    std::int64_t play(std::uint64_t currentTick, std::uint64_t previousTick, Track& track);

    void enumerateEvents(std::function<bool (const Event* pEvent, int index)> callback) const;

};
