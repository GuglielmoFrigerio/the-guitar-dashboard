/*
  ==============================================================================

    AudioBuffer.h
    Created: 2 Aug 2021 4:54:14pm
    Author:  gugli

  ==============================================================================
*/

#pragma once

class AudioBuffer 
{
private:
    float*  m_pBuffer;
    int     m_bufferLength;
    int     m_dataCount = 0;

public:
    AudioBuffer(int bufferLength);
    ~AudioBuffer();

    int add(const float* pData, int dataLength);

    const float* getBuffer() const {
        return m_pBuffer;
    }

    int getCount() const {
        return m_dataCount;
    }

    void empty() {
        m_dataCount = 0;
    }

    float computeSum(int sampleCount) const;
    float computeVolume(int sampleCount) const;
};
