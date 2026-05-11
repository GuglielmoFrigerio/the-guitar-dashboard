/*
  ==============================================================================

    MediaBay.cpp
    Created: 10 Jan 2026 3:03:42pm
    Author:  gugli

  ==============================================================================
*/

#include "MediaBay.h"
#include <stdexcept>

ne::MediaBay::MediaBay()
{
    auto currentFolder = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory();
    m_mediaFolder = currentFolder.getChildFile("../../../../../Resources");
	if (!m_mediaFolder.exists() || !m_mediaFolder.isDirectory())     {
        throw std::runtime_error("Media folder not found at expected location: " + m_mediaFolder.getFullPathName().toStdString());
    }
}

juce::AudioSampleBuffer* ne::MediaBay::getMediaBuffer(const std::string& mediaName, const std::string& mediaPath)
{
	auto mediaFile = m_mediaFolder.getChildFile(mediaPath);
    if (!mediaFile.existsAsFile()) {
        throw std::runtime_error("Media file not found: " + mediaFile.getFullPathName().toStdString());
	}   

    auto it = m_mediaMap.find(mediaName);
    if (it != m_mediaMap.end()) {
        return it->second.get();
    }
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(mediaFile));
    if (reader != nullptr) {
        auto newBuffer = std::make_unique<juce::AudioSampleBuffer>(static_cast<int>(reader->numChannels), static_cast<int>(reader->lengthInSamples));
        reader->read(newBuffer.get(), 0, static_cast<int>(reader->lengthInSamples), 0, true, true);
        juce::AudioSampleBuffer* bufferPtr = newBuffer.get();
        m_mediaMap[mediaName] = std::move(newBuffer);
        return bufferPtr;
    }
    throw std::runtime_error("Unsupported or corrupted audio file");
}
