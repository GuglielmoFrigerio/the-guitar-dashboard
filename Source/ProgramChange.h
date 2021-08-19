/*
  ==============================================================================

    ProgramChange.h
    Created: 14 Aug 2021 9:54:12am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct ProgramChange 
{
    juce::String    name;
    int             programNumber;
    int             sceneNumber;

    int getBankNumber() const {
        return programNumber / 128;
    }

    int getPatchNumber() const {
        return programNumber % 128;
    }
};