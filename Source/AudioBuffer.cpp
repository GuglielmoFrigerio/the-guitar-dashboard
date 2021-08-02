/*
  ==============================================================================

    AudioBuffer.cpp
    Created: 2 Aug 2021 4:54:14pm
    Author:  gugli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioBuffer.h"

AudioBuffer::AudioBuffer(int bufferLength)
{
    m_pBuffer = new float[bufferLength];
    m_bufferLength = bufferLength;
}

AudioBuffer::~AudioBuffer()
{
	delete[] m_pBuffer;
}

void AudioBuffer::add(const float* pData, int dataLength)
{
	auto roomLeft = m_bufferLength - m_dataCount;
	if (roomLeft < dataLength)
	{
		auto message = juce::String::formatted("AudioBuffer::add: buffer overflow. Requested %d, available %d", dataLength, roomLeft);
		throw std::runtime_error(message.toUTF8());
	}
}