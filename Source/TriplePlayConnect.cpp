/*
  ==============================================================================

    TriplePlayConnect.cpp
    Created: 30 Dec 2022 7:25:26pm
    Author:  gugli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TriplePlayConnect.h"

void TriplePlayConnect::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    auto midiInputCallbackPtr = m_midiInputCallbackPtr;
    if (midiInputCallbackPtr != nullptr)
        midiInputCallbackPtr->handleIncomingMidiMessage(source, message);

    if (message.isNoteOn()) {
        auto channel = message.getChannel();
        auto noteNumber = message.getNoteNumber();
        auto velocity = message.getVelocity();
        m_pMidiInputTarget->onNoteOn(channel, noteNumber, velocity);
    }
    if (message.isController()) {
        auto controllerNumber = message.getControllerNumber();
        auto controllerValue = message.getControllerValue();
    }
    if (message.isProgramChange()) {

        auto pcn = message.getProgramChangeNumber();
        if (onSongSelect != nullptr)
            onSongSelect(pcn);

    }
}

TriplePlayConnect::TriplePlayConnect(IMidiInputTarget* pMidiInputTarget)
    : m_pMidiInputTarget(pMidiInputTarget)
{
    auto inputDevices = juce::MidiInput::getAvailableDevices();
    for (auto& deviceInfo : inputDevices) {
        if (deviceInfo.name == "TriplePlay Connect") {
            m_midiInputPtr = juce::MidiInput::openDevice(deviceInfo.identifier, this); 
            m_midiInputPtr->start();
            break;
        }
    }
}

TriplePlayConnect::~TriplePlayConnect()
{
    if (m_midiInputPtr != nullptr) {
        m_midiInputPtr->stop();
        m_midiInputPtr = nullptr;
    }
}

void TriplePlayConnect::setMidiInputCallback(std::shared_ptr<juce::MidiInputCallback>& midiInputCallbackPtr)
{
    m_midiInputCallbackPtr = midiInputCallbackPtr;
}

void TriplePlayConnect::clearMidiInputCallback()
{
    m_midiInputCallbackPtr = nullptr;
}
