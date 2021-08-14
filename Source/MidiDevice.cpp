/*
  ==============================================================================

    MidiDevice.cpp
    Created: 14 Aug 2021 9:48:15am
    Author:  gugli

  ==============================================================================
*/

#include "MidiDevice.h"

MidiDevice::MidiDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId)
{
    m_midiOutPortPtr = juce::MidiOutput::openDevice(outputMidiPortId);
    m_midiInPortPtr = juce::MidiInput::openDevice(inputMidiPortId, this);
}
