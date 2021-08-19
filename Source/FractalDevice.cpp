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
#include "FractalDiscoverDevice.h"

#define MAX_SYSEX_MSG_LEN   80

FractalDevice::FractalDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId)
    :   MidiDevice(inputMidiPortId, outputMidiPortId)
{
    m_incomingMessageHandler = &FractalDevice::standardInputMessageHandler;
}

bool FractalDevice::queryDevice(const std::uint8_t* queryFirmwareMessage, int msgLmessageLength)
{
    m_queryFirmwareVersionAnswer.prepare();
    m_incomingMessageHandler = &FractalDevice::handleQueryFirmwareVersionResponse;

    jassert(msgLmessageLength < MAX_SYSEX_MSG_LEN);
    std::uint8_t sysexMessage[MAX_SYSEX_MSG_LEN];
    std::memcpy(sysexMessage, queryFirmwareMessage, msgLmessageLength);

    sendSysexMessage(sysexMessage, msgLmessageLength);
    auto [result, reason] = m_queryFirmwareVersionAnswer.waitForAnswer(200);
    return result;
}

void FractalDevice::standardInputMessageHandler(juce::MidiInput* , const juce::MidiMessage& message)
{
    DBG("[FractalDevice::standardInputMessageHandler] unexpected message received. Raw size is: " << message.getRawDataSize());
}

void FractalDevice::handleQueryFirmwareVersionResponse(juce::MidiInput* , const juce::MidiMessage& message)
{
    auto pData = message.getRawData();
    auto dataLength = message.getRawDataSize();
    if (message.isSysEx() && dataLength > 13)  {
        auto& data = m_queryFirmwareVersionAnswer.getAnswerData();
        data.major = pData[6];
        data.minor = pData[7];
        m_queryFirmwareVersionAnswer.provideAnswer();
    } else {
        m_queryFirmwareVersionAnswer.failOperation("Invalid MidiMessage received.");
    }
}

void FractalDevice::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    (this->*m_incomingMessageHandler)(source, message);
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

std::vector<std::unique_ptr<FractalDevice>> FractalDevice::loadAvailableDevices()
{
    std::vector<std::unique_ptr<FractalDevice>> returnCollection;

    const auto& inputInfoArray = juce::MidiInput::getAvailableDevices();
    const auto& outputInfoArray = juce::MidiOutput::getAvailableDevices();

    for (auto& inputInfo : inputInfoArray)
    {
        auto outputDeviceId = FractalDevice::findAssociatedOutput(inputInfo, outputInfoArray);
        if (outputDeviceId.isNotEmpty())
        {
            auto discoverDevice = std::make_unique<FractalDiscoverDevice>(inputInfo.identifier, outputDeviceId);
            auto actualDevicePtr = discoverDevice->discover();
            if (actualDevicePtr != nullptr)
                returnCollection.push_back(std::move(actualDevicePtr));
        }
    }

    return returnCollection;
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


