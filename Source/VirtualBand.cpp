/*
  ==============================================================================

    VirtualBand.cpp
    Created: 14 Aug 2021 10:37:58am
    Author:  gugli

  ==============================================================================
*/

#include "VirtualBand.h"

std::shared_ptr<MidiDevice> VirtualBand::getMidiDevice(const juce::String& deviceName)
{
    return std::shared_ptr<MidiDevice>();
}

void VirtualBand::loadDevices()
{
    juce::Thread::launch([this]() {
        m_fractalDevices = FractalDevice::loadAvailableDevices();
    });
}

void VirtualBand::teatProgramChange()
{
    for (auto& devicePtr : m_fractalDevices) {
        ProgramChange pc;

        pc.programNumber = 132;
        pc.sceneNumber = 3;

        devicePtr->SendProgramChange(pc, 1);
    }
}

