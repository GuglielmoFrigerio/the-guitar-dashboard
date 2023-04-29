/*
  ==============================================================================

    MidiRecorder.h
    Created: 29 Apr 2023 1:08:48pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include <JuceHeader.h>

class MidiRecorder {
private:
    double m_currentClick = 0.0;

private:
    void addQuarterNote(int noteNumber, juce::MidiMessageSequence& midiMessageSequence);

public:
    void test();
};
