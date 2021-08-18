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
    FractalDeviceType m_deviceType;

private:
    std::unique_ptr<FractalDevice> tryDiscover(FractalDeviceType deviceType);

public:
    FractalDiscoverDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId, FractalDeviceType deviceType);
    std::unique_ptr<FractalDevice> discover();
};
