/*
  ==============================================================================

    MarkerTrack.h
    Created: 4 Sep 2022 5:08:56pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <JuceHeader.h>
#include "Marker.h"
#include "DevicePatch.h"

class MarkerTrack {
private:
    std::vector<std::unique_ptr<Marker>> m_markers;

public:
    MarkerTrack(const juce::XmlElement* pPatchesElement);
    void enumerateDevicePatches(std::function<void(const DevicePatch* pDevicePatch, int index)> callback) const;
    uint64_t getClickTimepoint(int markerIndex);
    int getEventCount() const {
        return m_markers.size();
    }
};
