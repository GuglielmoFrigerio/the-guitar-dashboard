/*
  ==============================================================================

    NullMidiDevice.h
    Created: 16 Feb 2023 12:49:46pm
    Author:  Guglielmo

  ==============================================================================
*/

#pragma once
#include "MidiDevice.h"

class NullMidiDevice : public MidiDevice {
private:
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
};

