/*
  ==============================================================================

    MetronomeTrack.cpp
    Created: 29 Dec 2022 9:13:16am
    Author:  gugli

  ==============================================================================
*/

#include "MetronomeTrack.h"
#include "GuitarDashCommon.h"
#include "SampleEvent.h"

MetronomeTrack::MetronomeTrack(VirtualBand* pVirtualBand, int metronomeBeats)
{
    auto pSampleEngine = pVirtualBand->getSampleEngine();

    juce::String sampleName = "Stick.wav";

    for (auto tick = 0; tick < metronomeBeats; tick++) {
        std::int64_t clickTimepoint = tick * DefaultClicksPerBeat;
        std::unique_ptr<EventList> eventListPtr = std::make_unique<EventList>(clickTimepoint);
        std::unique_ptr<Event> sampleEventPtr = std::make_unique<SampleEvent>(pSampleEngine, sampleName, 1, 0.0);
        eventListPtr->addEvent(sampleEventPtr);
        addEventList(eventListPtr);
    }
}
