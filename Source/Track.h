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
#include <JuceHeader.h>
#include "EventList.h"
#include "IPlaybackTarget.h"

class MidiDevice;

class Track : public IPlaybackTarget {
protected:    // fields
    std::vector<std::unique_ptr<EventList>> m_eventList;
    int m_currentIndex = 0;
    std::int64_t m_seekClick;

protected:  // interface
    std::int64_t findCurrentIndex(std::int64_t currentClick);
    void loadFromXml(const juce::XmlElement* pRootElement, const std::string& elementName, std::function<std::unique_ptr<EventList>(const juce::XmlElement* pChildElement, std::int64_t clickTimepoint)> childElementHandler);

public:
    virtual ~Track() {}
    virtual void playFirstEvent() {}

    int getEventCount() const {
        return (int)m_eventList.size();
    }
    void play(std::int64_t currentClick, std::int64_t previousClick) override;
    void seek(std::int64_t currentClick, std::int64_t previousClick) override;

};
