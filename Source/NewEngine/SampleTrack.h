/*
  ==============================================================================

    SampleTrack.h
    Created: 6 Jan 2026 2:54:50pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "TrackBase.h"
#include "VoiceEngine.h"


namespace ne {
    class SampleTrack : public TrackBase {
    protected:
        const juce::AudioSampleBuffer* m_pClickSampleBuffer;
        VoiceEngine& m_voiceEngine;

    protected:
        SampleTrack(const juce::AudioSampleBuffer* pClickSampleBuffer, VoiceEngine& voiceEngine);

    public:
        ~SampleTrack() override = default;
    };
}
