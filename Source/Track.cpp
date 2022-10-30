/*
  ==============================================================================

    Track.cpp
    Created: 13 Aug 2021 7:45:44am
    Author:  gugli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Track.h"

void Track::addEvent(std::unique_ptr<Event>& newEvent)
{
    m_eventList.emplace_back(std::make_unique<EventList>(newEvent));
}

void Track::play(int index)
{
    if (index >= 0 && index < m_eventList.size())    {
        TimePoint tp;
        m_eventList[index]->play(tp, *this);
    } else {
        DBG("[Track::play] index is out of bounds");
    }
}

std::int64_t Track::play(std::int64_t currentClick, std::int64_t previousClick)
{
    auto eventListPtr = m_eventList[m_currentIndex].get();
    auto eventListClickTimepoint = eventListPtr->getClickTimepoint();
    while (eventListClickTimepoint <= currentClick && eventListClickTimepoint > previousClick) {
        eventListPtr->play(currentClick, previousClick, *this);
        if (m_currentIndex < (m_eventList.size() - 1)) {
            ++m_currentIndex;
            eventListPtr = m_eventList[m_currentIndex].get();
            eventListClickTimepoint = eventListPtr->getClickTimepoint();
        }
        else break;
    }
    return 0;
}
