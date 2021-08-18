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
    std::unique_ptr<FractalDevice> tryDiscover(FractalDeviceType deviceType);

public:
    FractalDiscoverDevice(const juce::String& inputMidiPortId, const juce::String& outputMidiPortId);
    std::unique_ptr<FractalDevice> discover();
};
