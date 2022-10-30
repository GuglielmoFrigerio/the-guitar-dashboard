/*
  ==============================================================================

    MarkerTrack.cpp
    Created: 4 Sep 2022 5:08:56pm
    Author:  gugli

  ==============================================================================
*/

#include "MarkerTrack.h"

const uint64_t DefaultClicksPerBeat = 480ull;

MarkerTrack::MarkerTrack(const juce::XmlElement* pPatchesElement)
{
    int64_t currentClickTimepoint = 0;
    for (auto* pPatchElement : pPatchesElement->getChildWithTagNameIterator("Patch")) {
        auto markerPtr = Marker::parse(pPatchElement, currentClickTimepoint);
        currentClickTimepoint = markerPtr->getClickTimepoint() + DefaultClicksPerBeat;
        m_markers.push_back(std::move(markerPtr));
    }
}

void MarkerTrack::enumerateDevicePatches(std::function<void(const DevicePatch* pDevicePatch, int index)> callback) const
{
    for (auto index = 0; index < m_markers.size(); index++)
    {
        auto& markerPtr = m_markers[index];
        auto pDevicePatch = markerPtr->getDevicePatch();
        callback(pDevicePatch, index);
    }
}
