/*
  ==============================================================================

    SampleTrack.cpp
    Created: 6 Jan 2026 2:54:50pm
    Author:  gugli

  ==============================================================================
*/

#include "SampleTrack.h"

namespace ne
{
    SampleTrack::SampleTrack(const juce::AudioSampleBuffer* pClickSampleBuffer, VoiceEngine& voiceEngine)
		: m_pClickSampleBuffer(pClickSampleBuffer), m_voiceEngine(voiceEngine)
    {
    }
}
