/*
  ==============================================================================

    SampleEvent.cpp
    Created: 13 Nov 2022 7:19:17pm
    Author:  gugli

  ==============================================================================
*/

#include <memory>
#include "SampleEvent.h"

std::int64_t SampleEvent::play(std::uint64_t currentClick, std::uint64_t previousClick, Track& track)
{
    m_pSampleEngine->addSampleEvent(this);
    return 0;
}

SampleEvent::SampleEvent(SampleEngine* pSampleEngine, juce::AudioFormatManager* pAudioFormatManager, const juce::String& sampleFilename, const juce::String& resourcePath, std::uint64_t id)
    : m_pSampleEngine(pSampleEngine), m_id(id)
{
    auto filename = resourcePath + juce::String("Samples/") + sampleFilename;
    auto fullPathname = juce::File::getCurrentWorkingDirectory().getChildFile(filename);
    juce::File file(fullPathname);
    std::unique_ptr<juce::AudioFormatReader> readerPtr(pAudioFormatManager->createReaderFor(file));
    if (readerPtr != nullptr) {
        m_sampleBuffer.setSize((int)readerPtr->numChannels, (int)readerPtr->lengthInSamples);
        readerPtr->read(&m_sampleBuffer, 0, (int)readerPtr->lengthInSamples, 0, true, true);
    }
}

bool SampleEvent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto numInputChannels = m_sampleBuffer.getNumChannels();
    auto numOutputChannels = bufferToFill.buffer->getNumChannels();

    auto outputSamplesRemaining = bufferToFill.numSamples;
    auto outputSamplesOffset = bufferToFill.startSample;

    auto again = true;
    while (outputSamplesRemaining > 0)
    {
        auto bufferSamplesRemaining = m_sampleBuffer.getNumSamples() - m_position;
        auto samplesThisTime = juce::jmin(outputSamplesRemaining, bufferSamplesRemaining);

        for (auto channel = 0; channel < numOutputChannels; ++channel)
        {
            bufferToFill.buffer->copyFrom(channel,
                outputSamplesOffset,
                m_sampleBuffer,
                channel % numInputChannels,
                m_position,
                samplesThisTime);
        }

        outputSamplesRemaining -= samplesThisTime;
        outputSamplesOffset += samplesThisTime;
        m_position += samplesThisTime;

        if (m_position == m_sampleBuffer.getNumSamples()) {
            m_position = 0;
            again = false;
        }
    }
    return again;
}
