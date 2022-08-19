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

class MidiEvent : public Event
{
private:    // fields
    juce::MidiMessage m_midiMessage;

private:    // overriden
    std::int64_t play(std::uint64_t currentTick, std::uint64_t previousTick, Track& track) override;

public:     // interface
    MidiEvent(const juce::MidiMessage& midiMessage);

};
