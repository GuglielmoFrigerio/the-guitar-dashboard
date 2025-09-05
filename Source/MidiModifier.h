/*
  ==============================================================================

    MidiModifier.h
    Created: 31 Aug 2025 5:23:48pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "IMidiOutput.h"


class MidiModifier {
private:
    const int m_midiChannel;
    int m_startValue;
    int m_endValue;
    int m_stepValue;
    int m_currentValue;
    int m_midiControl;
    IMidiOutput* m_pMidiOutput;

private:
    void sendMessage();

public:
    MidiModifier(const juce::XmlElement* pMidiModifierElement, IMidiOutput* pMidiOutput, const int midiChannel);

    void stepUp();
    void stepDown();

};
