/*
  ==============================================================================

    SampleEvent.h
    Created: 13 Nov 2022 7:19:17pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <string>
#include <JuceHeader.h>

class SampleEvent {
private:
    juce::AudioSampleBuffer m_sampleBuffer;

public:
    SampleEvent(juce::AudioFormatManager* pAudioFormatManager, const juce::String& sampleFilename, const juce::String& resourcePath);
};
