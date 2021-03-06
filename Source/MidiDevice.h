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
    bool m_inputStarted = false;
    int m_currentProgramNumber = -1;
    int m_currentSceneNumber = -1;

private:    // implementation

public:     // interface
    MidiDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId);
    ~MidiDevice();

    void start();
    virtual void sendProgramChange(const ProgramChange& programChange, int midiChannel);
};
