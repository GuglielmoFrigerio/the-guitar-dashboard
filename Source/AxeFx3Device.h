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
    AxeFx3Device(std::unique_ptr<juce::MidiOutput>& midiOutPortPtr, std::unique_ptr<juce::MidiInput>& midiInPortPtr);   

};
