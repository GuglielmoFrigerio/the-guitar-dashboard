/*
  ==============================================================================

    IDeviceHost.h
    Created: 14 Aug 2021 10:43:23am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include <JuceHeader.h>

class MidiDevice;

class IDeviceHost
{
public:
    virtual std::shared_ptr<MidiDevice> getMidiDevice(const juce::String& deviceName) = 0;

    virtual ~IDeviceHost()
    {
    }
};
