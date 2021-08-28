/*
  ==============================================================================

    AxeFx2Device.h
    Created: 18 Aug 2021 9:12:55pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "FractalDevice.h"

class AxeFx2Device : public FractalDevice 
{
public:
    AxeFx2Device(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId) : FractalDevice(inputMidiPortId, outputMidiPortId) {}

    virtual FractalDeviceType getDeviceType() override {
        return FractalDeviceType::AxeFxII;
    }
};
