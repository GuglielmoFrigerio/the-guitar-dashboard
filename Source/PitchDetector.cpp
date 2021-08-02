#include "PitchDetector.h"

PitchDetector::PitchDetector(double sampleRate)
{
	auto minimumFrequency = ReferenceFrequency * std::powf(2.0, ((float)MinimumMidiNote - 69.0) / 12.0);
	auto samples = std::round(sampleRate / minimumFrequency);
	m_sampleBufferPtr = std::make_unique<CircularBuffer>((int)(samples * 3));
}

void PitchDetector::addSamples(const float* pAudioSamples, int samplesCount)
{
	m_sampleBufferPtr->add(pAudioSamples, samplesCount);
}

float PitchDetector::computeSum(int sampleCount)
{
	float sum = NAN;
	auto required = sampleCount * 2;
	if (m_sampleBufferPtr->getCount() >= required)
	{
		sum = 0.0;
		m_sampleBufferPtr->doublePlay(sampleCount, [sum](float first, float second)
			{
				auto delta = first - second;
				sum += (delta * delta);
			});

	}

	return 0.0f;
}
