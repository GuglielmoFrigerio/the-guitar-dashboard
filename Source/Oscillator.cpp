//
//  Oscillator.cpp
//  SimpleEQ
//
//  Created by Guglielmo Frigerio on 07/07/21.
//

#define _USE_MATH_DEFINES
#include <cmath>

#include "Oscillator.h"

const float DoublePi = 2 * M_PI;

Oscillator::Oscillator(double sampleRate, float frequency) {
    m_stepPerSample = DoublePi * (frequency / sampleRate);    
}

void Oscillator::play(float *pBuffer, int bufferLength, float volume) {
    for (int index = 0; index < bufferLength; ++index)
    {
        auto sample = sin (m_currentRadians);
        *pBuffer += (sample * volume);
        ++pBuffer;
        m_currentRadians += m_stepPerSample;
        if (m_currentRadians >= DoublePi)
            m_currentRadians -= DoublePi;
    }
}

