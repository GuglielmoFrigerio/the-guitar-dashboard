#pragma once
#include <memory>
#include <cmath>
#include <vector>
#include "AudioBuffer.h"
#include "CorrelationSlot.h"

class PitchDetector {
private:	// private fields
	std::unique_ptr<AudioBuffer> m_sampleBufferPtr;
	const int MinimumMidiNote = 40;
	const int MaximumMidiNote = 77;
	float m_noiseGateThreashold;
	std::vector<CorrelationSlot> m_correlationSlots;
	int m_minimumSampleCount;

private:	// implementation
	float computeVolume(int sampleCount);
	static int computeSamplesFromMidiNote(int midiNote, double sampleRate);
	float computeSum(int sampleCount);

public:		// public interface
	PitchDetector(double sampleRate, float noiseGateThreashold);

	int detectPitch(const float* pAudioSamples, int samplesCount);


};