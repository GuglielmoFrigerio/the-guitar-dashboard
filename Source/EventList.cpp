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

EventList::EventList(std::int64_t clicktimepoint)
    :   m_clickTimepoint(clicktimepoint)
{
}

void EventList::addEvent(std::unique_ptr<Event>& eventPtr)
{
    m_events.emplace_back(std::move(eventPtr));
}

void EventList::play(const TimePoint& timepoint, Track& track)
{
    for (auto it = m_events.begin(); it != m_events.end(); ++it)
    {
        auto& eventPtr = * it;
        eventPtr->play(timepoint, track);
    }
}

std::int64_t EventList::play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track)
{
    beforePlaying();
    for (auto it = m_events.begin(); it != m_events.end(); ++it)
    {
        auto& eventPtr = *it;
        eventPtr->play(currentClick, previousClick, track);
    }
    afterPlaying();
    return std::int64_t();
}

void EventList::enumerateEvents(std::function<bool(const Event* pEvent, int index)> callback) const
{
    for (auto index = 0; index < m_events.size(); index++)
    {
        auto& eventPtr = m_events[index];
        if (!callback(eventPtr.get(), index))
            break;
    }
}
