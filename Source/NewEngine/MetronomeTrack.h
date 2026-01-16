/*
  ==============================================================================

    MetronomeTrack.h
    Created: 6 Jan 2026 12:39:47pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "SampleTrack.h"

namespace ne {
    class MetronomeTrack : public SampleTrack {
    private:
		const juce::AudioSampleBuffer* m_pClickSampleBuffer;
    public:
        MetronomeTrack(const juce::AudioSampleBuffer* pClickSampleBuffer);
        ~MetronomeTrack() override = default;
		void getNextAudioBlock(const RenderContext& renderContext) override;
    };
}
