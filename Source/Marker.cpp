/*
  ==============================================================================

    Marker.cpp
    Created: 30 Oct 2022 6:44:29pm
    Author:  gugli

  ==============================================================================
*/

#include "Marker.h"

Marker::Marker(const juce::XmlElement* pPatchElement, uint64_t clickTimepoint)
    :   m_devicePatch(DevicePatch::parse(pPatchElement, clickTimepoint))
{
    m_playOnNote = pPatchElement->getIntAttribute("playOnNote", m_playOnNote);
    m_minVelocity = pPatchElement->getIntAttribute("minVelocity", m_minVelocity);
}

std::unique_ptr<Marker> Marker::parse(const juce::XmlElement* pPatchElement, uint64_t clickTimepoint)
{
    return std::make_unique<Marker>(pPatchElement, clickTimepoint);
}
