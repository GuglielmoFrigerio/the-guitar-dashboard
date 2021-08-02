#include <stdexcept>
#include <JuceHeader.h>
#include "CircularBuffer.h"


CircularBuffer::CircularBuffer(int bufferLength)
{
	m_pBuffer = new float[bufferLength];
	m_bufferLength = bufferLength;
}

CircularBuffer::~CircularBuffer()
{
	delete[] m_pBuffer;
}

void CircularBuffer::add(const float* pData, int dataLength)
{
	if (roomLeft() < dataLength)
	{
		auto message = juce::String::formatted("CircularBuffer::add: buffer overflow. Requested %d, available %d", dataLength, roomLeft());
		throw std::runtime_error(message.toUTF8());
	}
	auto firstChunk = m_bufferLength - m_writeIndex;
	firstChunk = std::min(firstChunk, dataLength);

	std::memcpy((&m_pBuffer[m_writeIndex]), pData, firstChunk);
	auto leftChunk = dataLength - firstChunk;
	if (leftChunk > 0)
		std::memcpy(m_pBuffer, &pData[firstChunk], leftChunk);
	m_itemsCount += dataLength;
	m_writeIndex = (m_writeIndex + dataLength) % m_bufferLength;
}

void CircularBuffer::doublePlay(int windowSize, std::function<void(float, float)> sampleHandler)
{
	auto requestedSize = windowSize * 2;
	if (m_itemsCount < (requestedSize))
	{
		auto message = juce::String::formatted("CircularBuffer::doublePlay: not enough data: requested: %d, available %d ", requestedSize, m_itemsCount);
		throw std::runtime_error(message.toUTF8());
	}

	auto firstIndex = m_readIndex;
	auto secondIndex = (m_readIndex + windowSize) % m_bufferLength;
	while (windowSize > 0)
	{
		sampleHandler(m_pBuffer[firstIndex], m_pBuffer[secondIndex]);
		firstIndex = ++firstIndex % m_bufferLength;
		secondIndex = ++secondIndex % m_bufferLength;
		windowSize--;
	}
}

void CircularBuffer::empty(int dataLength)
{
	if (m_itemsCount < dataLength)
	{
		auto message = juce::String::formatted("CircularBuffer::empty: not enough data: requested: %d, available %d ", dataLength, m_itemsCount);
		throw std::runtime_error(message.toUTF8());
	}

	m_readIndex = (m_readIndex + dataLength) % m_bufferLength;
	m_itemsCount -= dataLength;
}
