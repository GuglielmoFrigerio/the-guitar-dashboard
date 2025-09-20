/*
  ==============================================================================

    MidiModifierTrigger.h
    Created: 20 Sep 2025 4:45:34pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MidiModifierTrigger {
private:
    double m_startValue;
    double m_endValue;
    double m_minValue;
    double m_maxValue;
    double m_stepValue;
    int m_midiTriggerNote;
    std::uint64_t m_initialDelay = 0;
    std::uint64_t m_rampLengthTick = 0;

public:
    MidiModifierTrigger(const juce::XmlElement* pMidiModifierElement);

    inline std::uint64_t getInitialDelay() const {
        return m_initialDelay;
    }

    inline std::uint64_t getRampLengthTick() const {
        return m_rampLengthTick;
    }
};
