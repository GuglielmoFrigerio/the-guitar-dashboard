/*
  ==============================================================================

    MidiDevice.cpp
    Created: 14 Aug 2021 9:48:15am
    Author:  gugli

  ==============================================================================
*/

#include "GuitarDashCommon.h"
#include "MidiDevice.h"


MidiDevice::MidiDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId)
{
    m_midiOutPortPtr = juce::MidiOutput::openDevice(outputMidiPortId);
    m_midiInPortPtr = juce::MidiInput::openDevice(inputMidiPortId, this);
}

void MidiDevice::start()
{
    m_midiInPortPtr->start();
}

void MidiDevice::SendProgramChange(const ProgramChange& programChange)
{
}
