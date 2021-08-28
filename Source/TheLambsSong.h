/*
  ==============================================================================

    TheLambsSong.h
    Created: 21 Aug 2021 7:04:54pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "Song.h"

class VirtualBand;
class MidiTrack;

class TheLambsSong : public Song
{
private:    // fields
    MidiTrack* m_pMidiTrack = nullptr;

public:
    TheLambsSong(const juce::XmlElement* pPatchesElement, const VirtualBand* pVirtualBand);

    virtual void activate() override;

    virtual void selectProgramChange(int programChangeIndex) override;
    virtual void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent) override;
};
