/*
  ==============================================================================

    MidiOutput.cpp
    Created: 22 Aug 2022 4:25:50pm
    Author:  Guglielmo

  ==============================================================================
*/

#include "MidiOutput.h"

MidiOutput::MidiOutput()
{
    auto outputDevices = juce::MidiOutput::getAvailableDevices();
    for (auto& outputInfo : outputDevices) {
        DBG("MidiDeviceInfo name: " << outputInfo.name << " id: " << outputInfo.identifier);
        if (outputInfo.name == "Microsoft GS Wavetable Synth") {
            m_outputPtr = juce::MidiOutput::openDevice(outputInfo.identifier);
        }
    }
}

void MidiOutput::setupBuffer()
{
    DBG("MidiOutput::setupBuffer");
}

void MidiOutput::addMessage(const juce::MidiMessage& midiMessage)
{
    DBG("MidiOutput::addMessage: " << midiMessage.getDescription());
    if (m_outputPtr != nullptr) {
        m_outputPtr->sendMessageNow(midiMessage);
    }
}

void MidiOutput::send()
{
    DBG("MidiOutput::send");
}
