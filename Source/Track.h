/*
  ==============================================================================

    Track.h
    Created: 13 Aug 2021 7:45:44am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <memory>
#include "EventList.h"
#include "IPlaybackTarget.h"

class MidiDevice;

class Track : public IPlaybackTarget {
protected:    // fields
    std::vector<std::unique_ptr<EventList>> m_eventList;
    int m_currentIndex = 0;

protected:  // interface
    void    addEvent(std::unique_ptr<Event>& newEvent);
    std::int64_t findCurrentIndex(std::int64_t currentClick);

public:
    virtual ~Track() {}
    virtual void playFirstEvent() {}

    int getEventCount() const {
        return (int)m_eventList.size();
    }
    std::int64_t play(std::int64_t currentClick, std::int64_t previousClick) override;

};
