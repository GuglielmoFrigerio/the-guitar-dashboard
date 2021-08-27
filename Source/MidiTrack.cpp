/*
  ==============================================================================

    MidiTrack.cpp
    Created: 14 Aug 2021 9:52:21am
    Author:  gugli

  ==============================================================================
*/

#include "MidiTrack.h"
#include "TimePoint.h"

void MidiTrack::loadFromPatches(const juce::XmlElement* pPatchesElement)
{
    for (auto* pPatchElement : pPatchesElement->getChildWithTagNameIterator("Patch")) {
        auto programChangeEvent = ProgramChangeEvent::parse(pPatchElement);
        addEvent(programChangeEvent);
    }
}

void MidiTrack::playFirstEvent()
{
    TimePoint tp;

    if (m_eventList.size() > 0)
        m_eventList[0]->play(tp, *this);
}

std::unique_ptr<Track> MidiTrack::loadFromPatchesElement(const juce::XmlElement* pPatchesElement, MidiDevice* pMidiDevice)
{
    auto newMidiTrack = std::make_unique<MidiTrack>(pMidiDevice);
    newMidiTrack->loadFromPatches(pPatchesElement);
    return newMidiTrack;
}
