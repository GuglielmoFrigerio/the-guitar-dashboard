/*
  ==============================================================================

    MidiOutput.h
    Created: 22 Aug 2022 4:25:50pm
    Author:  Guglielmo

  ==============================================================================
*/

#pragma once
#include "IMidiOutput.h"
#include "MidiMessageFilter.h"

class MidiOutput : public IMidiOutput {
private:    // fields
    std::shared_ptr<juce::MidiOutput> m_outputPtr;
    juce::MidiBuffer m_midiBuffer;
    MidiMessageFilter m_midiMessageFilter;

public:
    MidiOutput();
    MidiOutput(std::shared_ptr<juce::MidiOutput> midiOutputPtr);

private:    // IMidiOutput interface implementation
    void setupBuffer() override;
    void addMessage(const juce::MidiMessage& midiMessage) override;
    void send() override;
};
