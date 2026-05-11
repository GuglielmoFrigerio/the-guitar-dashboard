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
#include "MidiModifierTrigger.h"

class MidiModifier {
private:
    const int m_midiChannel;
    std::atomic<double> m_startValue;
    std::atomic<double> m_endValue;
    std::atomic<double> m_minValue;
    std::atomic<double> m_maxValue;
    std::atomic<double> m_stepValue;
    double m_currentValue;
    int m_midiControl;
    IMidiOutput* m_pMidiOutput;

    int m_lastMidiValue = -1;

    std::uint64_t m_initialDelay = 0;
    std::uint64_t m_rampLengthTick = 0;

    std::int64_t m_lastTick = 0;
    std::atomic<std::int64_t> m_beginTickpoint = 0;
    std::atomic<std::int64_t> m_endTickpoint = 0;

    std::unordered_map<int, MidiModifierTrigger> m_triggers;
    int m_minMidiVelocity;

private:
    void setupMinMax();
    void sendMessage(double value);

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

    void onTick(std::int64_t microSeconds);
    void onNoteOn(int midiNote, int velocity);
};
