/*
  ==============================================================================

    MusicSequencer.h
    Created: 31 Dec 2025 10:02:27am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <vector>
#include <memory>
#include "CommandQueue.h"
#include "TrackBase.h"
#include "TempoMap.h"
#include "MediaBay.h"

namespace ne {
    class MusicSequencer
    {
        std::int64_t m_currentSamplePosition = 0;
        int m_samplesPerBlock = 0;
        double m_sampleRate = 44100.0;
        CommandQueue m_commandQueue;
        bool m_playing = false;
        std::vector<std::unique_ptr<TrackBase>> m_tracks;
		TempoMap m_tempoMap;
		MediaBay m_mediaBay;

    public:
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);

    public:
        void uiPlay();
        void uiStop();
        void uiSetPositionSamples(std::int64_t newPos);
    };
}
