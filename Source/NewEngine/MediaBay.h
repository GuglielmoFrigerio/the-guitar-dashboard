/*
  ==============================================================================

    MediaBay.h
    Created: 10 Jan 2026 3:03:42pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <JuceHeader.h>

namespace ne {
    class MediaBay {
    private:
		std::unordered_map<std::string, std::unique_ptr<juce::AudioSampleBuffer>> m_mediaMap;

    public:
        juce::AudioSampleBuffer* getMediaBuffer(const std::string& mediaName, const juce::File& mediaFile);
		
    };
}