#include <limits>
#include "PitchDetector.h"

static const float ReferenceFrequency = 440.0;

int PitchDetector::computeSamplesFromMidiNote(int midiNote, double sampleRate)
{
	auto minimumFrequency = ReferenceFrequency * std::powf(2.0f, ((float)midiNote - 69.0f) / 12.0f);
	return (int)std::round(sampleRate / minimumFrequency);
}

PitchDetector::PitchDetector(double sampleRate, float noiseGateThreashold)
	: m_noiseGateThreashold(noiseGateThreashold), m_correlationSet(sampleRate)
{
	m_minimumSampleCount = computeSamplesFromMidiNote(MinimumMidiNote, sampleRate) * 2;
	m_sampleBufferPtr = std::make_unique<AudioBuffer>((int)(m_minimumSampleCount * 3));
}

int PitchDetector::detectPitch(const float* pAudioSamples, int samplesCount)
{
	int midiNote = -1;
	auto sampleCount = m_sampleBufferPtr->add(pAudioSamples, samplesCount);
	if (sampleCount >= m_minimumSampleCount) 
	{
		auto level = m_sampleBufferPtr->computeSum(m_minimumSampleCount);
		if (level > m_noiseGateThreashold)
		{
			midiNote = m_correlationSet.computeAutoCorrelation(m_sampleBufferPtr.get());
		}

		m_sampleBufferPtr->empty();
	}
	return midiNote;
}
