/*
  ==============================================================================

    SampleEngine.h
    Created: 27 Nov 2022 6:26:16pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <atomic>
#include <vector>
#include <memory>
#include <unordered_map>
#include <JuceHeader.h>

class SampleEvent;

class SampleEngine {
private:
    struct SampleEntry {
        SampleEvent* m_pSampleEvent;
        bool m_active;

        SampleEntry(SampleEvent* pSampleEvent) : m_pSampleEvent(pSampleEvent), m_active(true) {}
    };

    using SampleEntryVector = std::vector<SampleEntry>;
    std::atomic<SampleEntryVector*> m_pSamples;
    juce::AudioFormatManager m_formatManager;
    juce::String m_resourcePath;
    std::unordered_map<juce::String, std::unique_ptr<juce::AudioSampleBuffer>> m_sampleBufferMap;

public:
    SampleEngine(const juce::String& resourcePath);
    ~SampleEngine();
    void addSampleEvent(SampleEvent* pSampleEvent);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);

    juce::AudioSampleBuffer* getSampleBuffer(const juce::String& sampleName);
};
