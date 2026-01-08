/*
  ==============================================================================

    TrackBase.h
    Created: 6 Jan 2026 2:52:06pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace ne {
    class TrackBase {
        public:
        TrackBase() = default;
		virtual ~TrackBase() = default;

        virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill, std::int64_t samplePosition) = 0;

    };
}
