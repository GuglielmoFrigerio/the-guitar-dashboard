/*
  ==============================================================================

    MidiEventList.cpp
    Created: 21 Aug 2022 9:00:03pm
    Author:  gugli

  ==============================================================================
*/

#include "MidiEventList.h"
#include "MidiEvent.h"

void MidiEventList::beforePlaying()
{
    m_pMidiOutput->setupBuffer();
}

void MidiEventList::afterPlaying()
{
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
