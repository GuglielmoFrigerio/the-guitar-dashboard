/*
  ==============================================================================

    ProgramChange.h
    Created: 14 Aug 2021 9:54:12am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include <JuceHeader.h>

struct ProgramChange 
{
    ProgramChange(int programNumber, int sceneNumber, const juce::String& name);

    juce::String    name;
    int             programNumber;
    int             sceneNumber;

    int getBankNumber() const {
        return programNumber / 128;
    }

    int getPatchNumber() const {
        return programNumber % 128;
    }

    static ProgramChange parse(const juce::XmlElement* pPatchElement);
};