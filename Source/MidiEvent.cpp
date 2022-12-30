/*
  ==============================================================================

    MidiEvent.cpp
    Created: 20 Aug 2021 3:40:58pm
    Author:  gugli

  ==============================================================================
*/

#include "MidiEvent.h"

void MidiEvent::play(std::uint64_t , std::uint64_t , Track& )
{
    m_pMidiOutput->addMessage(m_midiMessage);
}

void MidiEvent::seek(std::uint64_t , std::uint64_t , Track& )
{
    m_pMidiOutput->addMessage(m_midiMessage);
}

MidiEvent::MidiEvent(const juce::MidiMessage& midiMessage, IMidiOutput* pMidiOutput)
    : m_midiMessage(midiMessage), m_pMidiOutput(pMidiOutput)
{
}
