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

class MidiDevice;

class Track {
private:    // fields
    std::list<std::unique_ptr<EventList>> m_eventList;

protected:  // interface
    void    addEvent(std::unique_ptr<Event>& newEvent);

public:
    virtual ~Track() {}
    virtual MidiDevice* getMidiDevice() const = 0;
    virtual int getMidiChannel() const = 0;
};
