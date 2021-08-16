/*
  ==============================================================================

    VirtualBand.cpp
    Created: 14 Aug 2021 10:37:58am
    Author:  gugli

  ==============================================================================
*/

#include "VirtualBand.h"
#include "FractalDevice.h"

std::shared_ptr<MidiDevice> VirtualBand::getMidiDevice(const juce::String& deviceName)
{
    return std::shared_ptr<MidiDevice>();
}

void VirtualBand::loadDevices()
{
    FractalDevice::loadAvailableDevices();
}

void VirtualBand::loadMidiPortInfo(juce::ComboBox& inputCombo, juce::ComboBox& outputCombo)
{
}
