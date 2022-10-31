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
    int     m_midiChannel = 1;
    MidiDevice* m_pMidiDevice;

private:    // implementation
    void    loadFromPatches(const juce::XmlElement* pPatchesElement);

public:
    MidiTrack(MidiDevice* pMidiDevice) : m_pMidiDevice(pMidiDevice) {}
    MidiTrack(MidiDevice* pMidiDevice, const juce::MidiMessageSequence* pMidiMessageSequence, IMidiOutput* pMidiOutput);

    virtual MidiDevice* getMidiDevice() const override
    {
        return m_pMidiDevice;
    }

    virtual int getMidiChannel() const override
    {
        return m_midiChannel;
    }

    static std::unique_ptr<Track> loadFromPatchesElement(const juce::XmlElement* pPatchesElement, MidiDevice* pMidiDevice);
    static std::unique_ptr<Track> loadFromMidiFile(std::shared_ptr<juce::MidiFile>& midiFilePtr, int trackIndex, MidiDevice* pMidiDevice, IMidiOutput* pMidiOutput);
};
