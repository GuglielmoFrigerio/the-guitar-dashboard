/*
  ==============================================================================

    ProgramChange.cpp
    Created: 14 Aug 2021 9:54:12am
    Author:  gugli

  ==============================================================================
*/

#include "GuitarDashCommon.h"
#include "ProgramChange.h"

ProgramChange::ProgramChange(int programNumber, int sceneNumber, const juce::String& name, int clickTimepoint)
    : programNumber(programNumber), sceneNumber(sceneNumber), name(name), clickTimepoint(uint64_t(clickTimepoint))
{
}

void ProgramChange::addMidiEvents(MidiEventList* pMidiEventListPtr, int midiChannel)
{
    auto bankNumber = getBankNumber();
    auto patchNumber = getPatchNumber();
    auto controlChangeMessage = juce::MidiMessage::controllerEvent(midiChannel, 0, bankNumber);
    pMidiEventListPtr->addMidiEvent(controlChangeMessage);

    auto programChangeMsg = juce::MidiMessage::programChange(midiChannel, patchNumber);
    pMidiEventListPtr->addMidiEvent(controlChangeMessage);

    controlChangeMessage = juce::MidiMessage::controllerEvent(midiChannel, 34, sceneNumber - 1);
    pMidiEventListPtr->addMidiEvent(controlChangeMessage);
}

ProgramChange ProgramChange::parse(const juce::XmlElement* pPatchElement, uint64_t clickTimepoint)
{
    auto programNumber = getElementValueAsInt(pPatchElement);
    auto sceneNumber = pPatchElement->getIntAttribute("scene");
    auto name = pPatchElement->getStringAttribute("name");
    auto ct = pPatchElement->getIntAttribute("clickTimepoint", (int)clickTimepoint);
    return ProgramChange(programNumber, sceneNumber, name, ct);
}
