#include "PitchDetector.h"

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

PitchDetector::PitchDetector(double sampleRate, float noiseGateThreashold)
	: m_noiseGateThreashold(noiseGateThreashold)
{
	auto minimumFrequency = ReferenceFrequency * std::powf(2.0, ((float)MinimumMidiNote - 69.0) / 12.0);
	auto samples = std::round(sampleRate / minimumFrequency);
	m_sampleBufferPtr = std::make_unique<AudioBuffer>((int)(samples * 3));
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
		auto level =  computeVolume(required);
		if (level > m_noiseGateThreashold) 
		{
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
		}

		m_sampleBufferPtr->empty();
	}

	return sum;
}
