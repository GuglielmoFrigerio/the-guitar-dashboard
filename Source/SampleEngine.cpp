/*
  ==============================================================================

    SampleEngine.cpp
    Created: 27 Nov 2022 6:26:16pm
    Author:  gugli

  ==============================================================================
*/

#include "SampleEngine.h"
#include "SampleEvent.h"

SampleEngine::SampleEngine(const juce::String& resourcePath)
    : m_resourcePath(resourcePath)
{
    m_formatManager.registerBasicFormats();
    m_pSamples.store(new SampleEntryVector());
}

SampleEngine::~SampleEngine()
{
    auto pSamples = m_pSamples.load();
    delete pSamples;
}

void SampleEngine::addSampleEvent(SampleEvent* pSampleEvent)
{
    DBG("SampleEngine::addSampleEvent");
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

juce::AudioSampleBuffer* SampleEngine::getSampleBuffer(const juce::String& sampleName)
{
    auto it = m_sampleBufferMap.find(sampleName);
    if (it == m_sampleBufferMap.end()) {
        auto filename = m_resourcePath + juce::String("Samples/") + sampleName;
        auto fullPathname = juce::File::getCurrentWorkingDirectory().getChildFile(filename);
        juce::File file(fullPathname);
        std::unique_ptr<juce::AudioFormatReader> readerPtr(m_formatManager.createReaderFor(file));
        if (readerPtr == nullptr) {
            return nullptr;
        }
        auto sampleBufferPtr = std::make_unique<juce::AudioSampleBuffer>();
        sampleBufferPtr->setSize((int)readerPtr->numChannels, (int)readerPtr->lengthInSamples);
        readerPtr->read(sampleBufferPtr.get(), 0, (int)readerPtr->lengthInSamples, 0, true, true);
        auto result = m_sampleBufferMap.insert({ sampleName, std::move(sampleBufferPtr)});
        it = result.first;
    }
    return it->second.get();
}
