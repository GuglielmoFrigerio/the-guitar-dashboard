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
#include "ProgramChangeEvent.h"
#include "IPlaybackTarget.h"

class MidiDevice;

class Track : public IPlaybackTarget {
protected:    // fields
    std::vector<std::unique_ptr<EventList>> m_eventList;
    int m_currentIndex = 0;

protected:  // interface
    void    addEvent(std::unique_ptr<Event>& newEvent);

public:
    virtual ~Track() {}
    virtual MidiDevice* getMidiDevice() const = 0;
    virtual int getMidiChannel() const = 0;
    virtual void play(int index);
    virtual void playFirstEvent() {}

    void enumerateProgramChanges(std::function<void(const ProgramChangeEvent* pProgramChangeEvent, int index)> callback) const;

    int getEventCount() const {
        return (int)m_eventList.size();
    }
    std::int64_t play(std::uint64_t currentClick, std::uint64_t previousClick) override;

};
