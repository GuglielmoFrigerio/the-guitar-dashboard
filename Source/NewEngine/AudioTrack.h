#pragma once

#include "SampleTrack.h"

namespace ne {
	class AudioTrack : public SampleTrack {
	private:
		// start offset for this track in musical ticks (PPQ units)
		std::int64_t m_startTick = 0;

	public:
		AudioTrack(const juce::AudioSampleBuffer* pClickSampleBuffer, VoiceEngine& voiceEngine);

		void setStartTick(std::int64_t tick) noexcept { m_startTick = tick; }
		std::int64_t getStartTick() const noexcept { return m_startTick; }

		void getNextAudioBlock(const RenderContext& renderContext) override;
	};
}