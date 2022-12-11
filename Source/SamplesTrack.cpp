/*
  ==============================================================================

    SamplesTrack.cpp
    Created: 11 Dec 2022 7:12:03pm
    Author:  gugli

  ==============================================================================
*/
#include <memory>
#include "SamplesTrack.h"
#include "SampleEvent.h"
#include "GuitarDashCommon.h"

SamplesTrack::SamplesTrack(const juce::XmlElement* pSamplesElement, VirtualBand* pVirtualBand, const juce::String& resourcesPath)
{
    auto pSampleEngine = pVirtualBand->getSampleEngine();
    auto pAudioFormatManager = pVirtualBand->getAudioFormatManager();
    std::unique_ptr<EventList> currentEventListPtr = nullptr;

    for (auto* pSampleElement : pSamplesElement->getChildWithTagNameIterator("Sample")) {
        auto sampleName = pSampleElement->getStringAttribute("name");
        auto tick = pSampleElement->getIntAttribute("tick");
        auto offset = pSampleElement->getIntAttribute("offset");

        std::int64_t clickTimepoint = tick * DefaultClicksPerBeat + offset;
        std::unique_ptr<Event> sampleEventPtr = std::make_unique<SampleEvent>(pSampleEngine, pAudioFormatManager, sampleName, resourcesPath, 0);

        if (currentEventListPtr == nullptr)
            currentEventListPtr = std::make_unique<EventList>(clickTimepoint);

        if (clickTimepoint > currentEventListPtr->getClickTimepoint()) {
            m_eventList.emplace_back(std::move(currentEventListPtr));
            currentEventListPtr = std::make_unique<EventList>(clickTimepoint);
        }
        currentEventListPtr->addEvent(sampleEventPtr);
    }
    if ((currentEventListPtr != nullptr) && (currentEventListPtr->getEventCount() > 0)) {
        m_eventList.emplace_back(std::move(currentEventListPtr));
    }
}
