/*
  ==============================================================================

    FractalDevice.cpp
    Created: 14 Aug 2021 9:48:31am
    Author:  gugli

  ==============================================================================
*/

#include <cstdint>
#include "GuitarDashCommon.h"
#include "FractalDevice.h"

FractalDevice::FractalDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId)
    :   MidiDevice(inputMidiPortId, outputMidiPortId)
{
}

void FractalDevice::queryDevice()
{
    std::uint8_t sysexdata[] = { 0xf0, 0x00, 0x01, 0x74, 0x10, 0x08, 0xdd, 0xf7 };
    sendSysexMessage(sysexdata, sizeof(sysexdata));
}

void FractalDevice::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
}

std::uint8_t FractalDevice::computeChecksum(const uint8_t* pData, int dataLength)
{
    uint8_t checkSum = pData[0];

    for (auto index = 1; index < dataLength; ++index)
        checkSum ^= pData[index];
    checkSum &= 0x7f;
    return checkSum;
}

void FractalDevice::sendSysexMessage(uint8_t* pSysexData, int dataLength)
{
    auto checkSum = computeChecksum(pSysexData, dataLength - 2);
    pSysexData[dataLength - 2] = checkSum;
    auto sysExMsg = juce::MidiMessage::createSysExMessage(pSysexData, dataLength);
    m_midiOutPortPtr->sendMessageNow(sysExMsg);
}

void FractalDevice::loadAvailableDevices()
{
    const auto& inputInfoArray = juce::MidiInput::getAvailableDevices();
    const auto& outputInfoArray = juce::MidiOutput::getAvailableDevices();

    int index = 1;
    for (auto& inputInfo : inputInfoArray)
    {
        auto outputDeviceId = FractalDevice::findAssociatedOutput(inputInfo, outputInfoArray);
        if (outputDeviceId.isNotEmpty())
        {
            auto newMidiDevice = std::make_unique<FractalDevice>(inputInfo.identifier, outputDeviceId);
            newMidiDevice->start();
            newMidiDevice->queryDevice();
            juce::Time::waitForMillisecondCounter(juce::Time::getMillisecondCounter() + 10000);
        }
    }
}

juce::String FractalDevice::findAssociatedOutput(const juce::MidiDeviceInfo& inputInfo, const juce::Array<juce::MidiDeviceInfo>& outputDeviceInfo)
{
    for (auto& outputInfo : outputDeviceInfo)
    {
        if (stringsAreSimilar(inputInfo.name, outputInfo.name, 6, 3))
            return  outputInfo.identifier;
    }
    return juce::String();
}


