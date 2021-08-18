/*
  ==============================================================================

    FractalDevice.h
    Created: 14 Aug 2021 9:48:31am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <JuceHeader.h>
#include "MidiDevice.h"
#include "ThreadResponse.h"

enum FractalDeviceType 
{
    AxeFxII,
    AxeFxIII
};

struct FirmwareInfo
{
    int major;
    int minor;
};

class FractalDevice : public MidiDevice
{
private:    // fields
    void (FractalDevice::* m_incomingMessageHandler)(juce::MidiInput* source, const juce::MidiMessage& message);
    ThreadResponse<FirmwareInfo> m_queryFirmwareVersionAnswer;

public:     // interface
    FractalDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId);

    static std::vector<std::unique_ptr<FractalDevice>> loadAvailableDevices();

protected:  // implementation
    bool queryDevice(const std::uint8_t* queryFirmwareMessage, int msgLmessageLength);

private:    // implementation
    void standardInputMessageHandler(juce::MidiInput* source, const juce::MidiMessage& message);
    void handleQueryFirmwareVersionResponse(juce::MidiInput* source, const juce::MidiMessage& message);

    virtual void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
    std::uint8_t computeChecksum(const uint8_t* pData, int dataLength);
    void sendSysexMessage(uint8_t* pData, int dataLength);
    static juce::String findAssociatedOutput(const juce::MidiDeviceInfo& inputInfo, const juce::Array<juce::MidiDeviceInfo>& outputDeviceInfo);
};
