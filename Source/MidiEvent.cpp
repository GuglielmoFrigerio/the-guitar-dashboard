/*
  ==============================================================================

    MidiEvent.cpp
    Created: 20 Aug 2021 3:40:58pm
    Author:  gugli

  ==============================================================================
*/

#include "MidiEvent.h"

std::int64_t MidiEvent::play(std::uint64_t currentTick, std::uint64_t previousTick, Track& track)
{
    return std::int64_t();
}

void MidiEvent::play(const TimePoint& timepoint, Track& track)
{
}

MidiEvent::MidiEvent(const juce::MidiMessage& midiMessage)
    : m_midiMessage(midiMessage)
{
}
