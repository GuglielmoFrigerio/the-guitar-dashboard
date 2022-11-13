/*
  ==============================================================================

    SampleEvent.cpp
    Created: 13 Nov 2022 7:19:17pm
    Author:  gugli

  ==============================================================================
*/

#include <memory>
#include "SampleEvent.h"

SampleEvent::SampleEvent(juce::AudioFormatManager* pAudioFormatManager, const juce::String& sampleFilename, const juce::String& resourcePath)
{
    auto filename = resourcePath + juce::String("Samples/") + sampleFilename;
    juce::File file(filename);
    std::unique_ptr<juce::AudioFormatReader> readerPtr(pAudioFormatManager->createReaderFor(file));
    if (readerPtr != nullptr) {
        m_sampleBuffer.setSize((int)readerPtr->numChannels, (int)readerPtr->lengthInSamples);
        readerPtr->read(&m_sampleBuffer, 0, (int)readerPtr->lengthInSamples, 0, true, true);
    }
}
