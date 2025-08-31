/*
  ==============================================================================

    MidiModifier.h
    Created: 31 Aug 2025 5:23:48pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MidiDevice.h"


class MidiModifier {
private:
    int m_minValue;
    int m_maxValue;
    int m_stepValue;
    int m_currentValue;
    MidiDevice* m_pMidiDevice;

public:
    MidiModifier(const juce::XmlElement* pPatchElement, MidiDevice* pMidiDevice);

};
