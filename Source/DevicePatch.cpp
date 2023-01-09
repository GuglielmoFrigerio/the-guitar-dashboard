/*
  ==============================================================================

    DevicePatch.cpp
    Created: 14 Aug 2021 9:54:12am
    Author:  gugli

  ==============================================================================
*/

#include "GuitarDashCommon.h"
#include "DevicePatch.h"

DevicePatch::DevicePatch(int programNumber, int sceneNumber, const juce::String& name, int clickTimepoint)
    : programNumber(programNumber), sceneNumber(sceneNumber), name(name), clickTimepoint(uint64_t(clickTimepoint))
{
}

void DevicePatch::addMidiEvents(MidiEventList* pMidiEventListPtr, int midiChannel)
{
    auto bankNumber = getBankNumber();
    auto patchNumber = getPatchNumber();
    auto controlChangeMessage = juce::MidiMessage::controllerEvent(midiChannel, 0, bankNumber);
    pMidiEventListPtr->addMidiEvent(controlChangeMessage);

    auto programChangeMsg = juce::MidiMessage::programChange(midiChannel, patchNumber);
    pMidiEventListPtr->addMidiEvent(programChangeMsg);

    controlChangeMessage = juce::MidiMessage::controllerEvent(midiChannel, 34, sceneNumber - 1);
    pMidiEventListPtr->addMidiEvent(controlChangeMessage);
}

DevicePatch DevicePatch::parse(const juce::XmlElement* pPatchElement, uint64_t clickTimepoint)
{
    auto programNumber = getElementValueAsInt(pPatchElement);
    auto sceneNumber = pPatchElement->getIntAttribute("scene");
    auto name = pPatchElement->getStringAttribute("name");
    auto ct = getTickTimepoint(pPatchElement, clickTimepoint);
    return DevicePatch(programNumber, sceneNumber, name, ct);
}
