/*
  ==============================================================================

    MidiEventList.h
    Created: 21 Aug 2022 9:00:03pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <cstdint>
#include "EventList.h"
#include "IMidiOutput.h"

class MidiEventList : public EventList {
private:
    IMidiOutput* m_pMidiOutput;

private:    // implementation
    void beforePlaying() override;
    void afterPlaying() override;

public:
    MidiEventList(std::uint64_t clickTimepoint, IMidiOutput* pMidiOutput);
    void addMidiEvent(const juce::MidiMessage& midiMessage);
    static std::unique_ptr<MidiEventList> parse(juce::XmlElement* pPatchElement, int midiChannel, uint64_t clickTimepoint, IMidiOutput* pMidiOutput);
};
