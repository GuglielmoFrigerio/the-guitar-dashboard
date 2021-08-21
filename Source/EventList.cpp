/*
  ==============================================================================

    EventList.cpp
    Created: 13 Aug 2021 11:30:45am
    Author:  gugli

  ==============================================================================
*/

#include "EventList.h"

EventList::EventList(std::unique_ptr<Event>& firstEvent)
{
    m_events.emplace_back(std::move(firstEvent));
}

void EventList::play(const TimePoint& timepoint, Track& track)
{
    for (auto it = m_events.begin(); it != m_events.end(); ++it)
    {
        auto& eventPtr = * it;
        eventPtr->play(timepoint, track);
    }
}
