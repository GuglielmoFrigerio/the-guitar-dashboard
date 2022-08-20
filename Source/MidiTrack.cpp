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

void MidiTrack::loadFromPatches(const juce::XmlElement* pPatchesElement)
{
    for (auto* pPatchElement : pPatchesElement->getChildWithTagNameIterator("Patch")) {
        auto programChangeEvent = ProgramChangeEvent::parse(pPatchElement);
        addEvent(programChangeEvent);
    }
}

MidiTrack::MidiTrack(MidiDevice* pMidiDevice, const juce::MidiMessageSequence* pMidiMessageSequence)
    : m_pMidiDevice(pMidiDevice)
{
    std::map<std::uint64_t, std::unique_ptr<EventList>> eventListMap;

    auto eventCount = pMidiMessageSequence->getNumEvents();
    for (auto index = 0; index < eventCount; ++index) {

        auto pMidiEventHolder = pMidiMessageSequence->getEventPointer(index);
        auto clickTimepoint = (std::uint64_t)pMidiEventHolder->message.getTimeStamp();
        auto it = eventListMap.find(clickTimepoint);

        if (it == eventListMap.end()) {
            auto result = eventListMap.emplace(std::make_pair(clickTimepoint, std::make_unique<EventList>(clickTimepoint)));
            it = result.first;
        }
        std::unique_ptr<Event> midiEventPtr = std::make_unique<MidiEvent>(pMidiEventHolder->message);
        it->second->addEvent(midiEventPtr);
    }

    for (auto it = eventListMap.begin(); it != eventListMap.end(); ++it) {
        m_eventList.emplace_back(std::move(it->second));
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

std::unique_ptr<Track> MidiTrack::loadFromMidiFile(std::shared_ptr<juce::MidiFile>& midiFilePtr, int trackIndex, MidiDevice* pMidiDevice)
{

    auto pMessageSequence = midiFilePtr->getTrack(trackIndex);
    return std::make_unique<MidiTrack>(pMidiDevice, pMessageSequence);
}
