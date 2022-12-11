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
    m_pSamples.store(new SampleEntryVector());
}

SampleEngine::~SampleEngine()
{
    auto pSamples = m_pSamples.load();
    delete pSamples;
}

void SampleEngine::addSampleEvent(SampleEvent* pSampleEvent)
{
    auto pNewSampleEntryVector =  new SampleEntryVector();
    auto pOldSampleEntryVector = m_pSamples.load();
    for (auto& entry : *pOldSampleEntryVector) {
        if (entry.m_active) {
            pNewSampleEntryVector->emplace_back(entry.m_pSampleEvent);
        }
    }
    pNewSampleEntryVector->emplace_back(pSampleEvent);
    m_pSamples.store(pNewSampleEntryVector);
    delete pOldSampleEntryVector;
}

void SampleEngine::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto sampleEntryVectorPtr = m_pSamples.load();
    for (auto& sampleEntry : *sampleEntryVectorPtr) {
        if (sampleEntry.m_active) {
            sampleEntry.m_active = sampleEntry.m_pSampleEvent->getNextAudioBlock(bufferToFill);            
        }
    }
}
