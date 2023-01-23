/*
  ==============================================================================

    Track.cpp
    Created: 13 Aug 2021 7:45:44am
    Author:  gugli

  ==============================================================================
*/

#include "Track.h"
#include "GuitarDashCommon.h"

std::int64_t Track::findCurrentIndex(std::int64_t currentClick)
{
    std::int64_t previousClick = -1;

    for (auto index = 0; index < m_eventList.size(); ++index) {
        auto clickTimepoint = m_eventList[index]->getClickTimepoint();
        if (clickTimepoint >= currentClick) {
            m_currentIndex = index;
            return previousClick;
        }
        previousClick = clickTimepoint;
    }
    return previousClick;
}

void Track::loadFromXml(const juce::XmlElement* pRootElement, const std::string& elementName, std::function<std::unique_ptr<EventList>(const juce::XmlElement* pChildElement, std::int64_t clickTimepoint)> childElementHandler)
{
    int64_t currentClickTimepoint = 0;
    for (auto* pChildElement : pRootElement->getChildWithTagNameIterator(elementName)) {
        auto ct = getClickTimepoint(pChildElement, currentClickTimepoint);
        auto eventListPtr = childElementHandler(pChildElement, ct);
        if (eventListPtr != nullptr) {
            m_eventList.emplace_back(std::move(eventListPtr));
        }
        currentClickTimepoint = ct + DefaultClicksPerBeat;
    }
}

void Track::play(std::int64_t currentClick, std::int64_t previousClick)
{
    if (previousClick >= currentClick) {
        previousClick = findCurrentIndex(currentClick);
    }

    auto previous = (m_seekClick == previousClick) ? previousClick - 1 : previousClick;
    auto eventListPtr = m_eventList[m_currentIndex].get();
    auto eventListClickTimepoint = eventListPtr->getClickTimepoint();
    while (eventListClickTimepoint <= currentClick && eventListClickTimepoint > previous) {
        eventListPtr->play(currentClick, previous, *this);
        if (m_currentIndex < (m_eventList.size() - 1)) {
            ++m_currentIndex;
            eventListPtr = m_eventList[m_currentIndex].get();
            eventListClickTimepoint = eventListPtr->getClickTimepoint();
        }
        else break;
    }
}

void Track::seek(std::int64_t currentClick, std::int64_t previousClick)
{
    findCurrentIndex(currentClick);
    m_eventList[m_currentIndex]->seek(currentClick, previousClick, *this);
    m_seekClick = currentClick;
}
