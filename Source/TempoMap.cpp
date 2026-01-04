/*
  ==============================================================================

    TempoMap.cpp
    Created: 2 Jan 2026 3:25:37pm
    Author:  gugli

  ==============================================================================
*/

#include "TempoMap.h"

namespace ne {

    void TempoMap::setTempo(double bpm)
    {
		m_tempoBPM = bpm;
        double beatsPerSecond = m_tempoBPM / 60.0;
        double ticksPerSecond = beatsPerSecond * PPQ;
        double secondsPerTick = 1.0 / ticksPerSecond;
        m_samplesPerTick = secondsPerTick * m_sampleRate;
    }

    void TempoMap::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
        m_samplesPerBlock = samplesPerBlockExpected;
        m_sampleRate = sampleRate;
    }

    SampleOffset TempoMap::ticksToSamples(TickOffset tickOffset) const
    {
        return static_cast<SampleOffset>(tickOffset * m_samplesPerTick);
    }

    TickOffset TempoMap::samplesToTicks(SampleOffset sampleOffset) const
    {
        return static_cast<TickOffset>(sampleOffset / m_samplesPerTick);
    }
}