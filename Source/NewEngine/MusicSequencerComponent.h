/*
  ==============================================================================

    MusicSequencerComponent.h
    Created: 2 Feb 2026 1:55:35pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MusicSequencer.h"

//==============================================================================
/*
*/
class MusicSequencerComponent  :    public juce::AudioAppComponent,
                                    public juce::Slider::Listener
{
private:
    ne::MusicSequencer m_musicSequencer;
    juce::Slider m_bpmSlider;
    juce::Label  m_bpmLabel;


public:
    MusicSequencerComponent();
    ~MusicSequencerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    void releaseResources() override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicSequencerComponent)
};
