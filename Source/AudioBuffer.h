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

    void add(const float* pData, int dataLength);
    
};
