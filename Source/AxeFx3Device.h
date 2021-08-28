/*
  ==============================================================================

    AxeFx3Device.h
    Created: 14 Aug 2021 9:48:43am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "FractalDevice.h"

class AxeFx3Device : public FractalDevice
{
public:
    AxeFx3Device(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId) : FractalDevice(inputMidiPortId, outputMidiPortId) {}

    virtual FractalDeviceType getDeviceType() override {
        return FractalDeviceType::AxeFxIII;
    }
};
