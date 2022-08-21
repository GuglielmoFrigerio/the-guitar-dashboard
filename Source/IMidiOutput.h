/*
  ==============================================================================

    IMidiOutput.h
    Created: 21 Aug 2022 9:02:15pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IMidiOutput {
public:
    virtual void setupBuffer() = 0;
    virtual void addMessage(const juce::MidiMessage& midiMessage) = 0;
    virtual void send() = 0;
};
