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
enum class FractalDeviceType;

class IDeviceHost
{
public:
    virtual MidiDevice* getDevice(FractalDeviceType deviceType) const = 0;

    virtual ~IDeviceHost()
    {
    }
};
