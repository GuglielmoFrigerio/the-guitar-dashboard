#pragma once

class CircularBuffer {
private:
	float*	m_pBuffer;
	int		m_bufferLength;

public:
	CircularBuffer(int bufferLength);
	~CircularBuffer();

	void add(const float* pData, int dataLength);

	int getCount();
};