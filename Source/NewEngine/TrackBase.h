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

    class TempoMap;

    struct RenderContext
    {
        const juce::AudioSourceChannelInfo& out;
        std::int64_t startSample;
        std::int64_t endSample;      // startSample + numSamples
        std::int64_t startTick;
        double samplesPerBeat;
        const TempoMap* tempoMap;    // non-owning pointer to TempoMap
    };

    class TrackBase {
        public:
        TrackBase() = default;
		virtual ~TrackBase() = default;

        virtual void getNextAudioBlock(const RenderContext& renderContext) = 0;

    };
}
