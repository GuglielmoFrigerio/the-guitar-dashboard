/*
  ==============================================================================

    CorrelationSet.h
    Created: 9 Aug 2021 10:37:59am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include "CorrelationSlot.h"

class AudioBuffer;

class CorrelationSet {
private:
    std::vector<CorrelationSlot> m_correlationSlots;
    const int MinimumMidiNote = 40;
    const int MaximumMidiNote = 77;

public:
    CorrelationSet(double sampleRate);

    int computeAutoCorrelation(const AudioBuffer* pAudioBuffer);

    void save(const char* pFilename) const;
};
