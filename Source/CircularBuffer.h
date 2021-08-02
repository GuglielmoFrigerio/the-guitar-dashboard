#pragma once
#include <functional>

class CircularBuffer {
private:
	float*	m_pBuffer;
	int		m_bufferLength;
	int		m_readIndex = 0;
	int		m_writeIndex = 0;
	int		m_itemsCount = 0;

public:
	CircularBuffer(int bufferLength);
	~CircularBuffer();

	void add(const float* pData, int dataLength);
	int roomLeft() 
	{
		return m_bufferLength - m_itemsCount;
	}

	int getCount()
	{
		return m_itemsCount;
	}

	void doublePlay(int windowSize, std::function<void(float, float)> sampleHandler);

	void empty(int dataLength);
};