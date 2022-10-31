/*
  ==============================================================================

    MidiEvent.cpp
    Created: 20 Aug 2021 3:40:58pm
    Author:  gugli

  ==============================================================================
*/

#include "MidiEvent.h"

std::int64_t MidiEvent::play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track)
{
    m_pMidiOutput->addMessage(m_midiMessage);
    return std::int64_t();
}

MidiEvent::MidiEvent(const juce::MidiMessage& midiMessage, IMidiOutput* pMidiOutput)
    : m_midiMessage(midiMessage), m_pMidiOutput(pMidiOutput)
{
}
