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
    AxeFx2Device(std::unique_ptr<juce::MidiOutput>& midiOutPortPtr, std::unique_ptr<juce::MidiInput>& midiInPortPtr) : FractalDevice(midiOutPortPtr, midiInPortPtr) {}

};
