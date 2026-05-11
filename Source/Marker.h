/*
  ==============================================================================

    Marker.h
    Created: 30 Oct 2022 6:44:29pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <cstdint>
#include <memory>
#include <JuceHeader.h>
#include "DevicePatch.h"

class Marker {
private:
    DevicePatch m_devicePatch;
    int m_playOnNote = -1;
    int m_minVelocity = 127;

public:
    Marker(const juce::XmlElement* pPatchElement, uint64_t clickTimepoint);

    static std::unique_ptr<Marker> parse(const juce::XmlElement* pPatchElement, uint64_t clickTimepoint);

    std::uint64_t getClickTimepoint() const {
        return m_devicePatch.clickTimepoint;
    }

    const DevicePatch* getDevicePatch() const {
        return &m_devicePatch;
    }

    int getPlayOnNote() const {
        return m_playOnNote;
    }

    int getMinVelocity() const {
        return m_minVelocity;
    }
};
