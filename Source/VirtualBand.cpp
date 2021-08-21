/*
  ==============================================================================

    VirtualBand.cpp
    Created: 14 Aug 2021 10:37:58am
    Author:  gugli

  ==============================================================================
*/

#include "VirtualBand.h"

void VirtualBand::loadDevices()
{
    juce::Thread::launch([this]() {
        m_fractalDevices = FractalDevice::loadAvailableDevices();
    });
}

void VirtualBand::testProgramChange()
{
    for (auto& devicePtr : m_fractalDevices) {
        ProgramChange pc(132, 3, "");

        devicePtr->sendProgramChange(pc, 1);
    }
}

MidiDevice* VirtualBand::getDevice(FractalDeviceType deviceType) const
{
    return nullptr;
}

