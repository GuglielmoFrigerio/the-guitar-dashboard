/*
  ==============================================================================

    MidiOutput.h
    Created: 22 Aug 2022 4:25:50pm
    Author:  Guglielmo

  ==============================================================================
*/

#pragma once
#include "IMidiOutput.h"

class MidiOutput : public IMidiOutput {
private:    // fields
    std::unique_ptr<juce::MidiOutput> m_outputPtr;
    juce::MidiBuffer m_midiBuffer;

public:
    MidiOutput();

private:    // IMidiOutput interface implementation
    void setupBuffer() override;
    void addMessage(const juce::MidiMessage& midiMessage) override;
    void send() override;
};
