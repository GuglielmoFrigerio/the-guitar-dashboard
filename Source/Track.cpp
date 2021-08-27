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

void Track::play(int index)
{
    if (index >= 0 && index < m_eventList.size())    {
        TimePoint tp;
        m_eventList[index]->play(tp, *this);
    } else {
        DBG("[Track::play] index is out of bounds");
    }
}

void Track::enumerateProgramChanges(std::function<void(const ProgramChangeEvent* pProgramChangeEvent, int index)> callback) const
{
    for (auto index = 0; index < m_eventList.size(); index++)
    {
        auto& eventList = m_eventList[index];
        eventList->enumerateEvents([this, index, callback](const Event* pEvent, int eventIndex) {
            const auto pProgramChangeEvent = dynamic_cast<const ProgramChangeEvent*>(pEvent);
            if (pProgramChangeEvent != nullptr) {
                callback(pProgramChangeEvent, index);
                return false;
            }
            return true;
        });
    }
}
