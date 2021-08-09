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

int AudioBuffer::add(const float* pData, int dataLength)
{
	auto roomLeft = m_bufferLength - m_dataCount;
	if (roomLeft < dataLength)
	{
		auto message = juce::String::formatted("AudioBuffer::add: buffer overflow. Requested %d, available %d", dataLength, roomLeft);
		throw std::runtime_error(message.toUTF8());
	}
	std::memcpy(&m_pBuffer[m_dataCount], pData, dataLength * sizeof(float));
	m_dataCount += dataLength;
	return m_dataCount;
}

float AudioBuffer::computeSum(int sampleCount) const
{
	float sum = NAN;
	sum = 0.0;

	auto pFirst = m_pBuffer;
	auto pSecond = &pFirst[sampleCount];

	while (sampleCount > 0)
	{
		auto delta = *pFirst - *pSecond;
		sum += (delta * delta);
		pFirst++;
		pSecond++;
		sampleCount--;
	}

	return sum;
}

float AudioBuffer::computeVolume(int sampleCount) const
{
	auto pSamples = m_pBuffer;
	float sum = 0.0;

	while (sampleCount > 0)
	{
		auto value = *pSamples;
		sum += (value * value);
		pSamples++;
		sampleCount--;
	}

	return sum;
}

