/*
  ==============================================================================

    TheLambsSong.h
    Created: 21 Aug 2021 7:04:54pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <tuple>
#include "Song.h"

class VirtualBand;
class MidiTrack;
class PlayerComponent;

class TheLambsSong : public Song
{
private:    // fields
    MidiTrack* m_pMidiTrack = nullptr;
    int m_selectedProgramIndex = 0;
    std::unique_ptr<juce::AudioFormatReaderSource> m_readerSourcePtr;
    juce::String m_trackName;

public:
    TheLambsSong(const juce::XmlElement* pPatchesElement, const VirtualBand* pVirtualBand);

    virtual void activate(juce::AudioFormatManager* pAudioFormatManager, juce::AudioTransportSource* pAudioTransportSource, PlayerComponent* pPlayerComponent) override;

    virtual void selectProgramChange(int programChangeIndex) override;
    virtual void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent) override;

    virtual std::tuple<int, int> getSelectedProgramInfo() const override ;
};
