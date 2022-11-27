/*
  ==============================================================================

    SampleEngine.cpp
    Created: 27 Nov 2022 6:26:16pm
    Author:  gugli

  ==============================================================================
*/

#include "SampleEngine.h"
#include "SampleEvent.h"

SampleEngine::SampleEngine()
{
    m_samples.store(std::make_shared<SampleEntryVector>());
}

void SampleEngine::addSampleEvent(SampleEvent* pSampleEvent)
{
    std::shared_ptr<SampleEntryVector> newSampleEntryVectorPtr = std::make_shared<SampleEntryVector>();
    std::shared_ptr<SampleEntryVector> oldSampleEntryVectorPtr = m_samples.load();
    for (auto& entry : *oldSampleEntryVectorPtr) {
        if (entry.m_active) {
            newSampleEntryVectorPtr->emplace_back(entry.m_pSampleEvent);
        }
    }
    newSampleEntryVectorPtr->emplace_back(pSampleEvent);
    m_samples.store(newSampleEntryVectorPtr);
}

void SampleEngine::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto sampleEntryVectorPtr = m_samples.load();
    for (auto& sampleEntry : *sampleEntryVectorPtr) {
        if (sampleEntry.m_active) {
            sampleEntry.m_active = sampleEntry.m_pSampleEvent->getNextAudioBlock(bufferToFill);            
        }
    }
}
