/*
  ==============================================================================

    AutomationTrack.cpp
    Created: 18 Dec 2022 5:10:28pm
    Author:  gugli

  ==============================================================================
*/
#include "GuitarDashCommon.h"
#include "AutomationTrack.h"
#include "AutomationEvent.h"

AutomationTrack::AutomationTrack(const juce::XmlElement* pPatchesElement, IAutomationTarget* pAutomationTarget)
{
    loadFromXml(pPatchesElement, "Patch", [this](const juce::XmlElement* pChildElement, std::int64_t clickTimepoint) {


        std::string actionName = pChildElement->getStringAttribute("action");
        if (actionName.length() > 0) {
            auto event = std::make_unique<AutomationEvent>(actionName);
            auto eventListPtr = std::make_unique<EventList>(std::move(event));
            return eventListPtr;
        }
        return std::unique_ptr<EventList>();
    });
}
