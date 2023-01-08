/*
  ==============================================================================

    AutomationTrack.cpp
    Created: 18 Dec 2022 5:10:28pm
    Author:  gugli

  ==============================================================================
*/
#include "GuitarDashCommon.h"
#include "AutomationTrack.h"

AutomationTrack::AutomationTrack(const juce::XmlElement* pPatchesElement, IAutomationTarget* pAutomationTarget)
{
    int64_t currentClickTimepoint = 0;
    for (auto* pPatchElement : pPatchesElement->getChildWithTagNameIterator("Patch")) {
        auto markerPtr = Marker::parse(pPatchElement, currentClickTimepoint);
        currentClickTimepoint = markerPtr->getClickTimepoint() + DefaultClicksPerBeat;
        m_markers.push_back(std::move(markerPtr));
    }
}
