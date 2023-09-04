/*
  ==============================================================================

    SampleEngine.cpp
    Created: 27 Nov 2022 6:26:16pm
    Author:  gugli

  ==============================================================================
*/

#include "SampleEngine.h"
#include "SampleEvent.h"

void SampleEngine::setAudioBufferSampleGain(juce::AudioSampleBuffer* pAudioBuffer, int channel, int sampleIndex, float gain)
{
    auto sample = pAudioBuffer->getSample(channel, sampleIndex);
    pAudioBuffer->setSample(channel, sampleIndex, sample * gain);

}

void SampleEngine::setAudioBufferGain(juce::AudioSampleBuffer* pAudioBuffer, float gain)
{
    jassert (pAudioBuffer->getNumChannels() == 2);
    auto sampleCount = pAudioBuffer->getNumSamples();
    for (auto sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++) {
        setAudioBufferSampleGain(pAudioBuffer, 0, sampleIndex, gain);
        setAudioBufferSampleGain(pAudioBuffer, 1, sampleIndex, gain);
    }
}

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

juce::AudioSampleBuffer* SampleEngine::getSampleBuffer(const juce::String& sampleName, float gain)
{
    auto it = m_sampleBufferMap.find(sampleName);
    if (it == m_sampleBufferMap.end()) {
        auto filename = m_resourcePath + juce::String("Samples/") + sampleName;
        auto fullPathname = juce::File::getCurrentWorkingDirectory().getChildFile(filename);
        juce::File file(fullPathname);
        auto pFormatReader = m_formatManager.createReaderFor(file);
        std::unique_ptr<juce::AudioFormatReader> readerPtr(pFormatReader);
        if (readerPtr == nullptr) {
            return nullptr;
        }
        auto sampleBufferPtr = std::make_unique<juce::AudioSampleBuffer>();
        sampleBufferPtr->setSize((int)readerPtr->numChannels, (int)readerPtr->lengthInSamples);
        readerPtr->read(sampleBufferPtr.get(), 0, (int)readerPtr->lengthInSamples, 0, true, true);
        setAudioBufferGain(sampleBufferPtr.get(), gain);
        auto result = m_sampleBufferMap.insert({ sampleName, std::move(sampleBufferPtr)});
        it = result.first;
    }
    return it->second.get();
}
