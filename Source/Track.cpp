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

void Track::loadFromXml(const juce::XmlElement* pRootElement, std::function<bool (const juce::String& elementName)> elementNameTest, std::function<std::unique_ptr<EventList>(const juce::XmlElement* pChildElement, std::int64_t clickTimepoint)> childElementHandler)
{
    int64_t currentClickTimepoint = 0;
    for (auto* pChildElement : pRootElement->getChildIterator()) {
        auto elementName = pChildElement->getTagName();
        if (elementNameTest(elementName)) {
            auto ct = getClickTimepoint(pChildElement, currentClickTimepoint);
            auto eventListPtr = childElementHandler(pChildElement, ct);
            if (eventListPtr != nullptr) {
                addEventList(eventListPtr);
            }
            currentClickTimepoint = ct + DefaultClicksPerBeat;
        }
    }
}

void Track::addEventList(std::unique_ptr<EventList>& eventListPtr)
{
    auto size = m_eventList.size();
    if (size > 0) {
        auto ct = m_eventList[size - 1]->getClickTimepoint();
        auto incomingCt = eventListPtr->getClickTimepoint();
        jassert(ct < incomingCt);
    }
    m_eventList.emplace_back(std::move(eventListPtr));
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
    if (m_currentIndex < m_eventList.size()) {
        m_eventList[m_currentIndex]->seek(currentClick, previousClick, *this);
    }
    m_seekClick = currentClick;
}
