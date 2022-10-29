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
#include "MidiOutput.h"

class MidiDevice : public juce::MidiInputCallback
{
protected:  // fields
    std::shared_ptr<juce::MidiOutput> m_midiOutPortPtr;
    std::unique_ptr<juce::MidiInput> m_midiInPortPtr;
    std::unique_ptr<MidiOutput> m_midiOutputPtr;
    bool m_inputStarted = false;
    int m_currentProgramNumber = -1;
    int m_currentSceneNumber = -1;

private:    // implementation

public:     // interface
    MidiDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId);
    ~MidiDevice();

    void start();
    virtual void sendProgramChange(const ProgramChange& programChange, int midiChannel);
    void loadProgramChange(const ProgramChange& programChange, int midiChannel);

    IMidiOutput* getMidiOutput() const {
        return m_midiOutputPtr.get();
    }
};
