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
    m_midiOutputPtr = std::make_unique<MidiOutput>(m_midiOutPortPtr);
}

MidiDevice::~MidiDevice()
{
    if (m_inputStarted)
        m_midiInPortPtr->stop();
}

void MidiDevice::start()
{
    m_midiInPortPtr->start();
    m_inputStarted = true;
}

void MidiDevice::sendProgramChange(const ProgramChange& programChange, int midiChannel)
{
    if (programChange.programNumber != m_currentProgramNumber) {
        auto bankNumber = programChange.getBankNumber();
        auto patchNumber = programChange.getPatchNumber();
        auto controlChangeMessage = juce::MidiMessage::controllerEvent(midiChannel, 0, bankNumber);
        m_midiOutPortPtr->sendMessageNow(controlChangeMessage);

        auto programChangeMsg = juce::MidiMessage::programChange(midiChannel, patchNumber);
        m_midiOutPortPtr->sendMessageNow(programChangeMsg);
        m_currentSceneNumber = -1;
        m_currentProgramNumber = programChange.programNumber;
    }

    if (programChange.sceneNumber != m_currentSceneNumber) {
        auto controlChangeMessage = juce::MidiMessage::controllerEvent(midiChannel, 34, programChange.sceneNumber - 1);
        m_midiOutPortPtr->sendMessageNow(controlChangeMessage);
        m_currentSceneNumber = programChange.sceneNumber;
    }
}
