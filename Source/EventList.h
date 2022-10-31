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
    std::int64_t m_clickTimepoint = 0;

protected: // interface
    virtual void beforePlaying() {}
    virtual void afterPlaying() {}

public:     // interface
    EventList(std::unique_ptr<Event>& firstEvent);
    EventList(std::int64_t clicktimepoint);

    void addEvent(std::unique_ptr<Event>& eventPtr);
    std::int64_t play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track) override;

    void enumerateEvents(std::function<bool (const Event* pEvent, int index)> callback) const;

    std::int64_t getClickTimepoint() const {
        return m_clickTimepoint;
    }

};
