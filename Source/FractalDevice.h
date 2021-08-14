/*
  ==============================================================================

    FractalDevice.h
    Created: 14 Aug 2021 9:48:31am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MidiDevice.h"

class FractalDevice : MidiDevice
{
public:
    virtual void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;

};
