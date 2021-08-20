/*
  ==============================================================================

    ProgramChangeEvent.cpp
    Created: 14 Aug 2021 10:06:59am
    Author:  gugli

  ==============================================================================
*/

#include "ProgramChangeEvent.h"
#include "Track.h"

ProgramChangeEvent::ProgramChangeEvent(const juce::XmlElement* pInputElement)
    :   programChange(ProgramChange::parse(pInputElement))
{
}

void ProgramChangeEvent::play(const TimePoint& timepoint, Track& track)
{
    track.sendProgramChange(*this); 
}

std::unique_ptr<ProgramChangeEvent> ProgramChangeEvent::parse(juce::XmlElement* pPatchElement)
{
    return std::make_unique<ProgramChangeEvent>(pPatchElement);
}
