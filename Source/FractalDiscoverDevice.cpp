/*
  ==============================================================================

    FractalDiscoverDevice.cpp
    Created: 18 Aug 2021 2:02:53pm
    Author:  gugli

  ==============================================================================
*/

#include "FractalDiscoverDevice.h"
#include "AxeFx3Device.h"
#include "AxeFx2Device.h"

std::uint8_t axeFx3QueryFirmwareMessage[] = { 0xf0, 0x00, 0x01, 0x74, 0x10, 0x08, 0xdd, 0xf7 };
std::uint8_t axeFx2QueryFirmwareMessage[] = { 0xf0, 0x00, 0x01, 0x74, 0x07, 0x08, 0xdd, 0xf7 };


std::unique_ptr<FractalDevice> FractalDiscoverDevice::tryDiscover(FractalDeviceType deviceType)
{
    if (deviceType == FractalDeviceType::AxeFxIII) {
        if (queryDevice(axeFx3QueryFirmwareMessage, sizeof(axeFx3QueryFirmwareMessage)))
            return std::make_unique<AxeFx3Device>(m_midiOutPortPtr, m_midiInPortPtr);
    }
    else {
        if (queryDevice(axeFx2QueryFirmwareMessage, sizeof(axeFx2QueryFirmwareMessage)))
            return std::make_unique<AxeFx2Device>(m_midiOutPortPtr, m_midiInPortPtr);

    }
    return std::unique_ptr<FractalDevice>();
}

FractalDiscoverDevice::FractalDiscoverDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId)
    : FractalDevice(inputMidiPortId, outputMidiPortId)
{
}

std::unique_ptr<FractalDevice> FractalDiscoverDevice::discover()
{
    start();

    auto devicePtr = tryDiscover(FractalDeviceType::AxeFxII);
    if (devicePtr != nullptr)
        return devicePtr;

    return tryDiscover(FractalDeviceType::AxeFxIII);
}


