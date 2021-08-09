/*
  ==============================================================================

    CorrelationSet.cpp
    Created: 9 Aug 2021 10:37:59am
    Author:  gugli

  ==============================================================================
*/

#include "GuitarDashCommon.h"
#include "CorrelationSet.h"
#include "AudioBuffer.h"

CorrelationSet::CorrelationSet(double sampleRate)
{
	for (auto midiNote = MinimumMidiNote; midiNote < MaximumMidiNote; ++midiNote)
	{
		auto samples = computeSamplesFromMidiNote(midiNote, sampleRate);
		m_correlationSlots.emplace_back(samples, midiNote);
	}
}

int CorrelationSet::computeAutoCorrelation(const AudioBuffer* pAudioBuffer)
{
	float minimimSum = std::numeric_limits<float>::max();
	int midiNote = -1;

	for (auto it = m_correlationSlots.begin(); it != m_correlationSlots.end(); ++it)
	{
		auto& correlationSlot = *it;
		correlationSlot.correlationSum = pAudioBuffer->computeSum(correlationSlot.sampleCount);
		if (correlationSlot.correlationSum < minimimSum)
		{
			minimimSum = correlationSlot.correlationSum;
			midiNote = correlationSlot.midiNote;
		}
	}

	return midiNote;
}

void CorrelationSet::save(const char* pFilename) const
{
	auto pFile = fopen(pFilename, "w");
	for (auto it = m_correlationSlots.begin(); it != m_correlationSlots.end(); ++it)
	{
		auto& correlationSlot = *it;
		fprintf(pFile, "%d;%g\n", correlationSlot.midiNote, correlationSlot.correlationSum);
	}
	fclose(pFile);
}
