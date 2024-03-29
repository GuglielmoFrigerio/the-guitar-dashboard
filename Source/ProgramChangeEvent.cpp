/*
  ==============================================================================

    ProgramChangeEvent.cpp
    Created: 14 Aug 2021 10:06:59am
    Author:  gugli

  ==============================================================================
*/

#include "ProgramChangeEvent.h"
#include "Track.h"
#include "MidiDevice.h"

ProgramChangeEvent::ProgramChangeEvent(const juce::XmlElement* pInputElement)
    :   programChange(ProgramChange::parse(pInputElement))
{
}

void ProgramChangeEvent::play(const TimePoint& , Track& track)
{
    auto pMidiDevice = track.getMidiDevice();
    auto midiChannel = track.getMidiChannel();
    if (pMidiDevice != nullptr)
        pMidiDevice->sendProgramChange(programChange, midiChannel);
}

std::int64_t ProgramChangeEvent::play(std::uint64_t currentTick, std::uint64_t previousTick, Track& track)
{
    return std::int64_t();
}

std::unique_ptr<Event> ProgramChangeEvent::parse(juce::XmlElement* pPatchElement)
{
    return std::make_unique<ProgramChangeEvent>(pPatchElement);
}
