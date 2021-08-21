/*
  ==============================================================================

    MidiTrack.cpp
    Created: 14 Aug 2021 9:52:21am
    Author:  gugli

  ==============================================================================
*/

#include "MidiTrack.h"

void MidiTrack::loadFromPatches(const juce::XmlElement* pPatchesElement)
{
    for (auto* pPatchElement : pPatchesElement->getChildWithTagNameIterator("Patch")) {
        auto programChangeEvent = ProgramChangeEvent::parse(pPatchElement);
        addEvent(programChangeEvent);
    }
}

std::unique_ptr<Track> MidiTrack::loadFromPatchesElement(const juce::XmlElement* pPatchesElement, MidiDevice* pMidiDevice)
{
    auto newMidiTrack = std::make_unique<MidiTrack>(pMidiDevice);
    newMidiTrack->loadFromPatches(pPatchesElement);
    return newMidiTrack;
}
