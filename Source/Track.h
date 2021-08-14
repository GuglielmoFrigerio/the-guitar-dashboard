/*
  ==============================================================================

    Track.h
    Created: 13 Aug 2021 7:45:44am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <list>
#include <memory>
#include "EventList.h"
#include "ProgramChangeEvent.h"

class Track {
private:    // fields
    std::list<std::unique_ptr<EventList>> m_eventList;

public:
    virtual void sendProgramChange(const ProgramChangeEvent& programChangeEvent) = 0;
};
