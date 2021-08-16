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
public:     // interface
    FractalDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId);

    void queryDevice();
    static void loadAvailableDevices();

private:    // implementation
    virtual void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
    std::uint8_t computeChecksum(const uint8_t* pData, int dataLength);
    void sendSysexMessage(uint8_t* pData, int dataLength);
    static juce::String findAssociatedOutput(const juce::MidiDeviceInfo& inputInfo, const juce::Array<juce::MidiDeviceInfo>& outputDeviceInfo);
};
