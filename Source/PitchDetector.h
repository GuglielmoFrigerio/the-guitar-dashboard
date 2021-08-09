#pragma once
#include <memory>
#include <cmath>
#include <vector>
#include "AudioBuffer.h"
#include "CorrelationSlot.h"
#include "CorrelationSet.h"

class PitchDetector {
private:	// private fields
	std::unique_ptr<AudioBuffer> m_sampleBufferPtr;
	float m_noiseGateThreashold;
	CorrelationSet	m_correlationSet;
	const int MinimumMidiNote = 40;
	int m_minimumSampleCount;

private:	// implementation
	static int computeSamplesFromMidiNote(int midiNote, double sampleRate);

public:		// public interface
	PitchDetector(double sampleRate, float noiseGateThreashold);

	int detectPitch(const float* pAudioSamples, int samplesCount);
	void saveCorrelationSet(const char* pFilename) const
	{
		m_correlationSet.save(pFilename);
	}

};