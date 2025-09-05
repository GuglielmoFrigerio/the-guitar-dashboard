/*
  ==============================================================================

    MidiTrack.h
    Created: 14 Aug 2021 9:52:21am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "Track.h"
#include "IMidiOutput.h"

class MidiDevice;

class MidiTrack : public Track
{
private:    // fields
    MidiDevice* m_pMidiDevice;

private:    // implementation
    void    loadFromPatches(const juce::XmlElement* pPatchesElement, const int midiChannel);

public:
    MidiTrack(MidiDevice* pMidiDevice) : m_pMidiDevice(pMidiDevice) {}
    MidiTrack(MidiDevice* pMidiDevice, const juce::MidiMessageSequence* pMidiMessageSequence, IMidiOutput* pMidiOutput);

    static std::unique_ptr<Track> loadFromPatchesElement(const juce::XmlElement* pPatchesElement, MidiDevice* pMidiDevice, int midiChannel);
    static std::unique_ptr<Track> loadFromMidiFile(std::shared_ptr<juce::MidiFile>& midiFilePtr, int trackIndex, MidiDevice* pMidiDevice, IMidiOutput* pMidiOutput);
};
