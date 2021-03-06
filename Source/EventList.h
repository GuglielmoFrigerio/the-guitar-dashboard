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

public:     // interface
    EventList(std::unique_ptr<Event>& firstEvent);
    virtual void play(const TimePoint& timepoint, Track& track) override;

    void enumerateEvents(std::function<bool (const Event* pEvent, int index)> callback) const;

};
