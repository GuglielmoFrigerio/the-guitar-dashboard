/*
  ==============================================================================

    MidiTrack.cpp
    Created: 14 Aug 2021 9:52:21am
    Author:  gugli

  ==============================================================================
*/

#include <map>
#include "MidiTrack.h"
#include "TimePoint.h"
#include "MidiEvent.h"
#include "MidiEventList.h"
#include "MidiDevice.h"
#include "GuitarDashCommon.h"

void MidiTrack::loadFromPatches(const juce::XmlElement* pPatchesElement)
{
    int64_t currentClickTimepoint = 0;
    for (auto* pPatchElement : pPatchesElement->getChildWithTagNameIterator("Patch")) {
        std::unique_ptr<EventList> programChangeEventsPtr = MidiEventList::parse(pPatchElement, m_midiChannel, currentClickTimepoint, m_pMidiDevice->getMidiOutput());
        currentClickTimepoint = programChangeEventsPtr->getClickTimepoint() + DefaultClicksPerBeat;
        m_eventList.emplace_back(std::move(programChangeEventsPtr));
    }
}

MidiTrack::MidiTrack(MidiDevice* pMidiDevice, const juce::MidiMessageSequence* pMidiMessageSequence, IMidiOutput* pMidiOutput)
    : m_pMidiDevice(pMidiDevice)
{
    std::map<std::uint64_t, std::unique_ptr<MidiEventList>> eventListMap;

    auto eventCount = pMidiMessageSequence->getNumEvents();
    for (auto index = 0; index < eventCount; ++index) {

        auto pMidiEventHolder = pMidiMessageSequence->getEventPointer(index);
        auto clickTimepoint = (std::uint64_t)pMidiEventHolder->message.getTimeStamp();
        auto it = eventListMap.find(clickTimepoint);

        if (it == eventListMap.end()) {
            auto result = eventListMap.emplace(std::make_pair(clickTimepoint, std::make_unique<MidiEventList>(clickTimepoint, pMidiOutput)));
            it = result.first;
        }
        it->second->addMidiEvent(pMidiEventHolder->message);
    }

    for (auto it = eventListMap.begin(); it != eventListMap.end(); ++it) {
        m_eventList.emplace_back(std::move(it->second));
    }

}

std::unique_ptr<Track> MidiTrack::loadFromPatchesElement(const juce::XmlElement* pPatchesElement, MidiDevice* pMidiDevice)
{
    auto newMidiTrack = std::make_unique<MidiTrack>(pMidiDevice);
    newMidiTrack->loadFromPatches(pPatchesElement);
    return newMidiTrack;
}

std::unique_ptr<Track> MidiTrack::loadFromMidiFile(std::shared_ptr<juce::MidiFile>& midiFilePtr, int trackIndex, MidiDevice* pMidiDevice, IMidiOutput* pMidiOutput)
{
    auto pMessageSequence = midiFilePtr->getTrack(trackIndex);
    return std::make_unique<MidiTrack>(pMidiDevice, pMessageSequence, pMidiOutput);
}
