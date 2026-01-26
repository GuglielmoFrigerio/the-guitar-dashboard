/*
  ==============================================================================

    MetronomeTrack.h
    Created: 6 Jan 2026 12:39:47pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "SampleTrack.h"
#include "VoiceEngine.h"

namespace ne {
    class NewMetronomeTrack : public SampleTrack {
    private:
		const juce::AudioSampleBuffer* m_pClickSampleBuffer;
		VoiceEngine& m_voiceEngine;

    public:
        NewMetronomeTrack(const juce::AudioSampleBuffer* pClickSampleBuffer, VoiceEngine& voiceEngine);
        ~NewMetronomeTrack() override = default;
		void getNextAudioBlock(const RenderContext& renderContext) override;
    };
}
