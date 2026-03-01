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

    struct RenderContext
    {
        const juce::AudioSourceChannelInfo& out;
        std::int64_t startSample;
        std::int64_t endSample;      // startSample + numSamples
        std::int64_t startTick;
		std::int64_t samplesPerBeat;        
    };

    class TrackBase {
        public:
        TrackBase() = default;
		virtual ~TrackBase() = default;

        virtual void getNextAudioBlock(const RenderContext& renderContext) = 0;

    };
}
