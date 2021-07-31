#define _USE_MATH_DEFINES
#include <cmath>
#include "Lfo.h"

const float DoublePi = 2 * M_PI;


Lfo::Lfo(double sampleRate, float frequency)
{
    m_stepPerSample = DoublePi * (frequency / sampleRate);
}

float Lfo::getNext()
{
    auto sample = sin(m_currentRadians);
    m_currentRadians += m_stepPerSample;
    if (m_currentRadians >= DoublePi)
        m_currentRadians -= DoublePi;
    return sample;
}
