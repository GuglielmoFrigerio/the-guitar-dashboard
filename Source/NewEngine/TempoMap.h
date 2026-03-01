/*
  ==============================================================================

    TempoMap.h
    Created: 2 Jan 2026 3:25:37pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace ne
{
	const double PPQ = 960.0;           // Pulses (ticks) per quarter note
    using SampleOffset = juce::int64;   // absolute sample position or offset
    using TickOffset = juce::int64;     // musical ticks (PPQ)
    using SampleIndex = int;            // offset inside current block (0..N-1)

    class TempoMap
    {
    private:
        int m_samplesPerBlock = 0;
        double m_sampleRate = 44100.0;
		double m_tempoBPM = 0.0;
		double m_samplesPerTick = 0.0;
		double m_samplesPerBeat = 0.0;
        std::atomic<double> m_pendingBPM { 120.0 };

    private:
        void setTempo(double bpm);

    public:
        TempoMap() = default;
		~TempoMap() = default;

        void applyPendingTempo();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
        void requestTempo(double bpm) { m_pendingBPM.store(bpm); }

		SampleOffset ticksToSamples(TickOffset tickOffset) const;
		TickOffset samplesToTicks(SampleOffset sampleOffset) const;

		double getSamplesPerBeat() const { return m_samplesPerBeat; }
    };
}

