#include "PitchDetector.h"

PitchDetector::PitchDetector(double sampleRate)
{
	auto minimumFrequency = ReferenceFrequency * std::powf(2.0, ((float)MinimumMidiNote - 69.0) / 12.0);
}

void PitchDetector::addSamples(const float* pAudioSamples, int samplesCount)
{
	m_sampleBufferPtr->add(pAudioSamples, samplesCount);
}

float PitchDetector::computeSum(int sampleCount)
{
	return 0.0f;
}
