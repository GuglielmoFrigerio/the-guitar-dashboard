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
    class NewMetronomeTrack : public SampleTrack {
    private:
		const juce::AudioSampleBuffer* m_pClickSampleBuffer;
    public:
        NewMetronomeTrack(const juce::AudioSampleBuffer* pClickSampleBuffer);
        ~NewMetronomeTrack() override = default;
		void getNextAudioBlock(const RenderContext& renderContext) override;
    };
}
