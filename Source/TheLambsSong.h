/*
  ==============================================================================

    TheLambsSong.h
    Created: 21 Aug 2021 7:04:54pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <tuple>
#include "Song.h"
#include "Marker.h"

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
    std::vector<Marker> m_markers;
    const int m_previousGuardTime = 1.0;

private:
    void nextMarker(juce::AudioTransportSource* pAudioTransportSource) override;
    void previousMarker(juce::AudioTransportSource* pAudioTransportSource) override;
    void updateMarkers(double position, PlayerComponent* pPlayerComponent) override;

public:
    TheLambsSong(const juce::XmlElement* pPatchesElement, const VirtualBand* pVirtualBand);
    ~TheLambsSong() override {
    }

    void activate(juce::AudioFormatManager* pAudioFormatManager, juce::AudioTransportSource* pAudioTransportSource, PlayerComponent* pPlayerComponent) override;

    void selectProgramChange(int programChangeIndex) override;
    void updateProgramChangesList(ProgramChangesComponent* pProgramChangesComponent) override;

    std::tuple<int, int> getSelectedProgramInfo() const override;
};
