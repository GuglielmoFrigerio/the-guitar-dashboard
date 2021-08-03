#pragma once
#include <memory>
#include <cmath>
#include "AudioBuffer.h"
#include "CorrelationSlot.h"

class PitchDetector {
private:	// private fields
	std::unique_ptr<AudioBuffer> m_sampleBufferPtr;
	const int MinimumMidiNote = 40;
	const int MaximumMidiNote = 77;
	const float ReferenceFrequency = 440.0;
	float m_noiseGateThreashold;
	CorrelationSlot* m_pCorrelationSlots;
	int	m_correlationSlots;

private:	// implementation
	float computeVolume(int sampleCount);

public:		// public interface
	PitchDetector(double sampleRate, float noiseGateThreashold);

	int detectPitch(const float* pAudioSamples, int samplesCount);

	void addSamples(const float* pAudioSamples, int samplesCount);

	float computeSum(int sampleCount);

};