#include "GuitarDashCommon.h"
#include "Lfo.h"


Lfo::Lfo(double sampleRate, float frequency)
{
    m_stepPerSample = DoublePi * (frequency / (float)sampleRate);
}

float Lfo::getNext()
{
    auto sample = sin(m_currentRadians);
    m_currentRadians += m_stepPerSample;
    if (m_currentRadians >= DoublePi)
        m_currentRadians -= DoublePi;
    return sample;
}
