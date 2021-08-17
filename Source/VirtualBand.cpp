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
    juce::Thread::launch([]() {
        FractalDevice::loadAvailableDevices();
    });
}

void VirtualBand::loadMidiPortInfo(juce::ComboBox& inputCombo, juce::ComboBox& outputCombo)
{
    const auto& inputInfoArray = juce::MidiInput::getAvailableDevices();
    int index = 1;
    for (auto& inputInfo : inputInfoArray)
    {
        auto item = inputInfo.name + " (" + inputInfo.identifier + ")";
        inputCombo.addItem(item, index++);
    }

    const auto& outputInfoArray = juce::MidiOutput::getAvailableDevices();
    for (auto& outputInfo : outputInfoArray)
    {
        auto item = outputInfo.name + " (" + outputInfo.identifier + ")";
        outputCombo.addItem(item, index++);
    }
}
