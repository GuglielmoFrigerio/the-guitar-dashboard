//
//  Oscillator.cpp
//  SimpleEQ
//
//  Created by Guglielmo Frigerio on 07/07/21.
//

#define _USE_MATH_DEFINES
#include <cmath>
#include "Oscillator.h"
#include "GuitarDashCommon.h"

Oscillator::Oscillator(double sampleRate, float frequency) 
{
    m_stepPerSample = DoublePi * (frequency / (float)sampleRate);    
}

void Oscillator::play(float *pBuffer, int bufferLength, IModulationSource* pModulationSource) {
    for (int index = 0; index < bufferLength; ++index)
    {
        auto sample = sin (m_currentRadians);
        *pBuffer += (sample * pModulationSource->getNext());
        ++pBuffer;
        m_currentRadians += m_stepPerSample;
        if (m_currentRadians >= DoublePi)
            m_currentRadians -= DoublePi;
    }
}

void Oscillator::play(float* pBuffer, int bufferLength, float volume)
{
    FixedModulation fm(volume);
    play(pBuffer, bufferLength, &fm);
}

