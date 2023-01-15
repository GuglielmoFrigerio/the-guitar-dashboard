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
    loadFromXml(pPatchesElement, "Patch", [this, pAutomationTarget](const juce::XmlElement* pChildElement, std::int64_t clickTimepoint) {
        juce::String actionName = pChildElement->getStringAttribute("action");
        if (actionName.length() > 0) {
            std::unique_ptr<Event> eventPtr = std::make_unique<AutomationEvent>(actionName, pAutomationTarget);
            auto eventListPtr = std::make_unique<EventList>(eventPtr, clickTimepoint);
            return eventListPtr;
        }
        return std::unique_ptr<EventList>();
    });
}
