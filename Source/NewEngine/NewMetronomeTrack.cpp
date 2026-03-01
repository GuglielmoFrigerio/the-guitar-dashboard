/*
  ==============================================================================

    MetronomeTrack.cpp
    Created: 6 Jan 2026 12:39:47pm
    Author:  gugli

  ==============================================================================
*/

#include "NewMetronomeTrack.h"

namespace ne {

    NewMetronomeTrack::NewMetronomeTrack(const juce::AudioSampleBuffer* pClickSampleBuffer, VoiceEngine& voiceEngine)
		: m_pClickSampleBuffer(pClickSampleBuffer), m_voiceEngine(voiceEngine)
    {
    }

    void NewMetronomeTrack::getNextAudioBlock(const RenderContext& renderContext)
    {
		auto offset = renderContext.startSample % renderContext.samplesPerBeat;
        if (offset < renderContext.out.numSamples) {
			m_voiceEngine.trigger(m_pClickSampleBuffer, offset, 1.0f);
        }
	}
}
