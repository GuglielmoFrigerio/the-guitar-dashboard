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
#include "SampleEngine.h"
#include "Event.h"

class SampleEvent : public Event {
private:    // fields
    juce::AudioSampleBuffer m_sampleBuffer;
    std::uint64_t m_id;
    SampleEngine* m_pSampleEngine;

private:    // implementation
    std::int64_t play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track) override;

public:     // public interface
    SampleEvent(SampleEngine* pSampleEngine, juce::AudioFormatManager* pAudioFormatManager, const juce::String& sampleFilename, const juce::String& resourcePath, std::uint64_t id);
    bool getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    std::uint64_t getId() const {
        return m_id;
    }
};
