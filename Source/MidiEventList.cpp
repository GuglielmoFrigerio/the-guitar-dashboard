/*
  ==============================================================================

    MidiEventList.cpp
    Created: 21 Aug 2022 9:00:03pm
    Author:  gugli

  ==============================================================================
*/

#include "MidiEventList.h"
#include "MidiEvent.h"
#include "DevicePatch.h"


void MidiEventList::beforePlaying()
{
    if (m_pMidiOutput != nullptr)
        m_pMidiOutput->setupBuffer();
}

void MidiEventList::afterPlaying()
{
    if (m_pMidiOutput != nullptr)
        m_pMidiOutput->send();
}

void MidiEventList::beforeSeeking()
{
    if (m_pMidiOutput != nullptr)
        m_pMidiOutput->setupBuffer();
}

void MidiEventList::afterSeeking()
{
    if (m_pMidiOutput != nullptr)
        m_pMidiOutput->send();
}

MidiEventList::MidiEventList(std::uint64_t clickTimepoint, IMidiOutput* pMidiOutput)
    :   EventList(clickTimepoint), m_pMidiOutput(pMidiOutput)
{
}

void MidiEventList::addMidiEvent(const juce::MidiMessage& midiMessage)
{
    std::unique_ptr<Event> midiEventPtr = std::make_unique<MidiEvent>(midiMessage, m_pMidiOutput);
    addEvent(midiEventPtr);
}

std::unique_ptr<MidiEventList> MidiEventList::parse(juce::XmlElement* pPatchElement, int midiChannel, uint64_t clickTimepoint, IMidiOutput* pMidiOutput)
{
    auto programChangePtr = DevicePatch::parse(pPatchElement, clickTimepoint);
    auto eventListPtr = std::make_unique<MidiEventList>(programChangePtr.clickTimepoint, pMidiOutput);
    programChangePtr.addMidiEvents(eventListPtr.get(), midiChannel);
    return eventListPtr;
}
