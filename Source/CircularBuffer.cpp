#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int bufferLength)
{
	m_pBuffer = new float[bufferLength];
}

CircularBuffer::~CircularBuffer()
{
	delete[] m_pBuffer;
}

void CircularBuffer::add(const float* pData, int dataLength)
{
}
