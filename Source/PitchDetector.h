#pragma once
#include <memory>
#include <cmath>
#include "CircularBuffer.h"

class PitchDetector {
private:
	std::unique_ptr<CircularBuffer> m_sampleBufferPtr;
	const int MinimumMidiNote = 40;
	const float ReferenceFrequency = 440.0;

public:
	PitchDetector(double sampleRate);

	int detectPitch(const float* pAudioSamples, int samplesCount);

	void addSamples(const float* pAudioSamples, int samplesCount);

	float computeSum(int sampleCount);

};