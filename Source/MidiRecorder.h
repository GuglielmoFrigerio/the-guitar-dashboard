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
#include "PlaybackEngine.h"

class MidiRecorder : public juce::MidiInputCallback {
private:
    double m_currentClick = 0.0;
    PlaybackEngine* m_pPlaybackEngine;
    juce::MidiMessageSequence m_midiMessageSequence;

private:
    void addQuarterNote(int noteNumber, juce::MidiMessageSequence& midiMessageSequence);
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
    juce::File getFilename();

public:
    MidiRecorder(PlaybackEngine* pPlaybackEngine);
    void test();
    void saveFile();
};
