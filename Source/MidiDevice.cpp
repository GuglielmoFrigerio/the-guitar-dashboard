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

MidiDevice::MidiDevice(std::unique_ptr<juce::MidiOutput>& midiOutPortPtr, std::unique_ptr<juce::MidiInput>& midiInPortPtr)
    :   m_midiOutPortPtr(std::move(midiOutPortPtr)), m_midiInPortPtr(std::move(midiInPortPtr))
{
}

void MidiDevice::start()
{
    m_midiInPortPtr->start();
}

void MidiDevice::SendProgramChange(const ProgramChange& programChange)
{
}
