/*
  ==============================================================================

    FractalDiscoverDevice.h
    Created: 18 Aug 2021 2:02:53pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include "FractalDevice.h"


class FractalDiscoverDevice : public FractalDevice {
private:
    bool tryDiscover(FractalDeviceType deviceType);

public:
    FractalDiscoverDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId);
    FractalDeviceType discover();

    virtual FractalDeviceType getDeviceType() override {
        throw std::runtime_error("FractalDiscoverDevice does not support 'getDeviceType'");
    }
};
