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
    double m_startValue;
    double m_endValue;
    double m_minValue;
    double m_maxValue;
    double m_stepValue;
    double m_currentValue;
    int m_midiControl;
    int m_midiTriggerNote;
    IMidiOutput* m_pMidiOutput;

    int m_lastMidiValue = -1;

    std::uint64_t m_initialDelay = 0;
    std::uint64_t m_rampLengthTick = 0;

    std::uint64_t m_lastTick = 0;
    std::int64_t m_beginTickpoint;
    std::uint64_t m_endTickpoint;

private:
    void sendMessage();

public:
    MidiModifier(const juce::XmlElement* pMidiModifierElement, IMidiOutput* pMidiOutput, const int midiChannel);

    void stepUp();
    void stepDown();

    bool keyPressed(const juce::KeyPress& key);
    void start();
    void end();

    int getCurrentValue() const {
        return static_cast<int>(m_currentValue);
    }

    void onTick(std::uint64_t currentTick);
    void onNoteOn(int midiNote);
};
