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

MidiOutput::MidiOutput(std::shared_ptr<juce::MidiOutput> midiOutputPtr)
    : m_outputPtr(midiOutputPtr)
{
}

void MidiOutput::setupBuffer()
{
    m_midiBuffer.clear();
    DBG("MidiOutput::setupBuffer");
}

void MidiOutput::addMessage(const juce::MidiMessage& midiMessage)
{
    if (m_midiMessageFilter.canSendMessage(midiMessage)) {
        m_midiBuffer.addEvent(midiMessage, 0);
        DBG("MidiOutput::addMessage: " << midiMessage.getDescription());
    }
}

void MidiOutput::send()
{
    if (m_outputPtr != nullptr) {
        m_outputPtr->sendBlockOfMessagesNow(m_midiBuffer);
    }
    DBG("MidiOutput::send");
}
