/*
  ==============================================================================

    MidiDevice.h
    Created: 14 Aug 2021 9:48:15am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include <JuceHeader.h>
#include "ProgramChange.h"

class MidiDevice : public juce::MidiInputCallback
{
protected:  // fields
    std::unique_ptr<juce::MidiOutput> m_midiOutPortPtr;
    std::unique_ptr<juce::MidiInput> m_midiInPortPtr;

private:    // implementation

public:     // interface
    MidiDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId);
    MidiDevice(std::unique_ptr<juce::MidiOutput>& midiOutPortPtr, std::unique_ptr<juce::MidiInput>& midiInPortPtr);

    void start();
    virtual void SendProgramChange(const ProgramChange& programChange);
};
