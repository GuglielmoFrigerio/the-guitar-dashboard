#include <limits>
#include "PitchDetector.h"

static const float ReferenceFrequency = 440.0;


float PitchDetector::computeVolume(int sampleCount)
{
	auto pSamples = m_sampleBufferPtr->getBuffer();
	float sum = 0.0;

	while (sampleCount > 0)
	{
		auto value = *pSamples;
		sum += (value * value);
		pSamples++;
		sampleCount--;
	}

	return sum;
}

int PitchDetector::computeSamplesFromMidiNote(int midiNote, double sampleRate)
{
	auto minimumFrequency = ReferenceFrequency * std::powf(2.0f, ((float)midiNote - 69.0f) / 12.0f);
	return (int)std::round(sampleRate / minimumFrequency);
}

PitchDetector::PitchDetector(double sampleRate, float noiseGateThreashold)
	: m_noiseGateThreashold(noiseGateThreashold)
{
	m_minimumSampleCount = computeSamplesFromMidiNote(MinimumMidiNote, sampleRate) * 2;
	m_sampleBufferPtr = std::make_unique<AudioBuffer>((int)(m_minimumSampleCount * 3));
	for (auto midiNote = MinimumMidiNote; midiNote < MaximumMidiNote; ++midiNote)
	{
		auto samples = computeSamplesFromMidiNote(midiNote, sampleRate);
		m_correlationSlots.emplace_back(samples, midiNote);
	}
}

int PitchDetector::detectPitch(const float* pAudioSamples, int samplesCount)
{
	int midiNote = -1;
	float minimimSum = std::numeric_limits<float>::max();
	auto sampleCount = m_sampleBufferPtr->add(pAudioSamples, samplesCount);
	if (sampleCount >= m_minimumSampleCount) 
	{
		auto level = computeVolume(m_minimumSampleCount);
		if (level > m_noiseGateThreashold)
		{
			for (auto it = m_correlationSlots.begin(); it != m_correlationSlots.end(); ++it)
			{
				auto& correlationSlot = *it;
				correlationSlot.correlationSum = computeSum(correlationSlot.sampleCount);
				if (correlationSlot.correlationSum < minimimSum) 
				{
					minimimSum = correlationSlot.correlationSum;
					midiNote = correlationSlot.midiNote;
				}
			}
		}

		m_sampleBufferPtr->empty();
	}
	return midiNote;
}

float PitchDetector::computeSum(int sampleCount)
{
	float sum = NAN;
	sum = 0.0;

	auto pFirst = m_sampleBufferPtr->getBuffer();
	auto pSecond = &pFirst[sampleCount];

	while (sampleCount > 0)
	{
		auto delta = *pFirst - *pSecond;
		sum += (delta * delta);
		pFirst++;
		pSecond++;
		sampleCount--;
	}

	return sum;
}
