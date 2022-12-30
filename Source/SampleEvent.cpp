/*
  ==============================================================================

    SampleEvent.cpp
    Created: 13 Nov 2022 7:19:17pm
    Author:  gugli

  ==============================================================================
*/

#include <memory>
#include "SampleEvent.h"

void SampleEvent::play(std::uint64_t, std::uint64_t, Track& )
{
    m_pSampleEngine->addSampleEvent(this);
}

void SampleEvent::seek(std::uint64_t , std::uint64_t , Track& )
{
}

SampleEvent::SampleEvent(SampleEngine* pSampleEngine, const juce::String& sampleFilename, std::uint64_t id)
    : m_pSampleEngine(pSampleEngine), m_id(id)
{
    m_pSampleBuffer = pSampleEngine->getSampleBuffer(sampleFilename);
}

bool SampleEvent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto numInputChannels = m_pSampleBuffer->getNumChannels();
    auto numOutputChannels = bufferToFill.buffer->getNumChannels();

    auto outputSamplesRemaining = bufferToFill.numSamples;
    auto outputSamplesOffset = bufferToFill.startSample;

    auto again = true;
    while (outputSamplesRemaining > 0)
    {
        auto bufferSamplesRemaining = m_pSampleBuffer->getNumSamples() - m_position;
        auto samplesThisTime = juce::jmin(outputSamplesRemaining, bufferSamplesRemaining);

        for (auto channel = 0; channel < numOutputChannels; ++channel)
        {
            bufferToFill.buffer->copyFrom(channel,
                outputSamplesOffset,
                *m_pSampleBuffer,
                channel % numInputChannels,
                m_position,
                samplesThisTime);
        }

        outputSamplesRemaining -= samplesThisTime;
        outputSamplesOffset += samplesThisTime;
        m_position += samplesThisTime;

        if (m_position == m_pSampleBuffer->getNumSamples()) {
            m_position = 0;
            again = false;
            break;
        }
    }
    return again;
}
