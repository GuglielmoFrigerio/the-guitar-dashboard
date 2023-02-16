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
#include "DevicePatch.h"
#include "MidiOutput.h"

class MidiDevice : public juce::MidiInputCallback
{
protected:  // fields
    std::shared_ptr<juce::MidiOutput> m_midiOutPortPtr = nullptr;
    std::unique_ptr<juce::MidiInput> m_midiInPortPtr = nullptr;
    std::unique_ptr<MidiOutput> m_midiOutputPtr = nullptr;
    bool m_inputStarted = false;
    int m_currentProgramNumber = -1;
    int m_currentSceneNumber = -1;

protected:    // implementation
    MidiDevice();

public:     // interface
    MidiDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId);
    ~MidiDevice();

    void start();
    virtual void sendProgramChange(const DevicePatch& programChange, int midiChannel);
    void loadProgramChange(const DevicePatch& programChange, int midiChannel);

    IMidiOutput* getMidiOutput() const {
        return m_midiOutputPtr.get();
    }
};
