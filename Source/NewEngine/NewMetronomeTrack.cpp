/*
  ==============================================================================

    MetronomeTrack.cpp
    Created: 6 Jan 2026 12:39:47pm
    Author:  gugli

  ==============================================================================
*/

#include "NewMetronomeTrack.h"
#include <cmath>

namespace ne {

    NewMetronomeTrack::NewMetronomeTrack(const juce::AudioSampleBuffer* pClickSampleBuffer, VoiceEngine& voiceEngine)
		: SampleTrack(pClickSampleBuffer, voiceEngine)
    {
    }

    void NewMetronomeTrack::getNextAudioBlock(const RenderContext& renderContext)
    {
        if (renderContext.samplesPerBeat <= 0.0)
            return;

        // compute offset in samples from the start of the beat
        double samplesPerBeat = renderContext.samplesPerBeat;
        double rem = std::fmod(static_cast<double>(renderContext.startSample), samplesPerBeat);
        if (rem < 0.0)
            rem += samplesPerBeat;
        int offset = static_cast<int>(std::lround(rem));

        if (offset < renderContext.out.numSamples) {
            m_voiceEngine.trigger(m_pClickSampleBuffer, offset, 1.0f);
        }
	}
}
