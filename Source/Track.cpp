/*
  ==============================================================================

    Track.cpp
    Created: 13 Aug 2021 7:45:44am
    Author:  gugli

  ==============================================================================
*/

#include "Track.h"

void Track::addEvent(std::unique_ptr<Event>& newEvent)
{
    m_eventList.emplace_back(std::make_unique<EventList>(newEvent));
}
