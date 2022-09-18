/*
  ==============================================================================

    MidiEvent.h
    Created: 20 Aug 2021 3:40:58pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Event.h"
#include "IMidiOutput.h"

class MidiEvent : public Event
{
private:    // fields
    juce::MidiMessage m_midiMessage;
    IMidiOutput* m_pMidiOutput;

private:    // overriden
    std::int64_t play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track) override;
    void play(const TimePoint& timepoint, Track& track) override;

public:     // interface
    MidiEvent(const juce::MidiMessage& midiMessage, IMidiOutput* pMidiOutput);

};
