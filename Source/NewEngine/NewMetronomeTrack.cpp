/*
  ==============================================================================

    MetronomeTrack.cpp
    Created: 6 Jan 2026 12:39:47pm
    Author:  gugli

  ==============================================================================
*/

#include "NewMetronomeTrack.h"

namespace ne {

    NewMetronomeTrack::NewMetronomeTrack(const juce::AudioSampleBuffer* pClickSampleBuffer)
        : m_pClickSampleBuffer(pClickSampleBuffer)
    {
    }

    void NewMetronomeTrack::getNextAudioBlock(const RenderContext& renderContext)
    {
        //auto clickLength = m_pClickSampleBuffer->getNumSamples();
        //auto samplesPerBeat = 44100; // Assuming 120 BPM and 44100 Hz sample rate for simplicity
        //for (auto i = 0; i < bufferToFill.numSamples; ++i) {
        //    auto globalSampleIndex = samplePosition + i;
        //    if (globalSampleIndex % samplesPerBeat < clickLength) {
        //        for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
        //            auto clickSample = m_pClickSampleBuffer->getSample(channel % m_pClickSampleBuffer->getNumChannels(), globalSampleIndex % samplesPerBeat);
        //            bufferToFill.buffer->addSample(channel, bufferToFill.startSample + i, clickSample);
        //        }
        //    }
        //}
	}
}
