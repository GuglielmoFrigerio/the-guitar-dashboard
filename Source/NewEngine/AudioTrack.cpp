#include "AudioTrack.h"
#include "TempoMap.h"

namespace ne {
	AudioTrack::AudioTrack(const juce::AudioSampleBuffer* pClickSampleBuffer, VoiceEngine& voiceEngine)
		: SampleTrack(pClickSampleBuffer, voiceEngine)
	{
	}

	void AudioTrack::getNextAudioBlock(const RenderContext& renderContext)
	{
		// Guard conditions
		if (m_pClickSampleBuffer == nullptr)
			return;
		if (renderContext.out.numSamples <= 0)
			return;
		if (renderContext.tempoMap == nullptr)
			return;

		// Convert track start tick to absolute sample position using TempoMap

		auto absoluteStartSample = renderContext.tempoMap->ticksToSamples(m_startTick);

		// Compute offset within this block
		auto sampleOffsetInBlock = absoluteStartSample - renderContext.startSample;

		if (sampleOffsetInBlock >= 0 && sampleOffsetInBlock < renderContext.out.numSamples) {
			m_voiceEngine.trigger(m_pClickSampleBuffer, static_cast<int>(sampleOffsetInBlock), 1.0f);
		}
	}
}