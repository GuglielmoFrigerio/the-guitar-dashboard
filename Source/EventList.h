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
#include "IPlayable.h"
#include "Event.h"

class EventList : public IPlayable
{
private:    // fields
    std::vector<std::unique_ptr<Event>> m_events;

public:     // interface
    virtual void play(const TimePoint& timepoint) override;
};
