/*
  ==============================================================================

    DevicePatch.h
    Created: 14 Aug 2021 9:54:12am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include <JuceHeader.h>
#include "MidiEventList.h"


struct DevicePatch 
{
    DevicePatch(int programNumber, int sceneNumber, const juce::String& name, int clickTimepoint);

    juce::String    name;
    int             programNumber;
    int             sceneNumber;
    uint64_t        clickTimepoint;

    int getBankNumber() const {
        return programNumber / 128;
    }

    int getPatchNumber() const {
        return programNumber % 128;
    }

    void addMidiEvents(MidiEventList* pMidiEventListPtr, int midiChannel);

    static DevicePatch parse(const juce::XmlElement* pPatchElement, uint64_t clickTimepoint);
};