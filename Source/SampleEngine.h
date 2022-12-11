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

public:
    SampleEngine();
    ~SampleEngine();
    void addSampleEvent(SampleEvent* pSampleEvent);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
};
