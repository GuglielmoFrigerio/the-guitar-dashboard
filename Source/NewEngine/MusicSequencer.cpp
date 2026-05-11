/*
  ==============================================================================

    MusicSequencer.cpp
    Created: 31 Dec 2025 10:02:27am
    Author:  gugli

  ==============================================================================
*/

#include "MusicSequencer.h"
#include "NewMetronomeTrack.h"
#include "AudioTrack.h"
#include "TempoMap.h"

namespace ne {

    void MusicSequencer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
        m_samplesPerBlock = samplesPerBlockExpected;
        m_sampleRate = sampleRate;
        m_currentSamplePosition = 0;
		m_tempoMap.prepareToPlay(samplesPerBlockExpected, sampleRate);
        m_tempoMap.requestTempo(m_currentTempoBpm);
    }

    void MusicSequencer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
    {
        // Process any pending commands
        Command cmd;
        while (m_commandQueue.popCommand(cmd))
        {
            switch (cmd.m_type)
            {
            case CommandType::Play:
                m_playing = true;
                break;

            case CommandType::Stop:
                m_playing = false;
                break;

            case CommandType::SetBpm:
                // Handle set BPM command
                break;

            case CommandType::SeekSamples:
                m_currentSamplePosition = cmd.m_samplePosition;
                break;

            default:
                break;
            }
        }
		m_tempoMap.applyPendingTempo();
        if (m_playing) {
            RenderContext renderContext {
                bufferToFill,
                m_currentSamplePosition,
                m_currentSamplePosition + bufferToFill.numSamples,
                m_tempoMap.samplesToTicks(m_currentSamplePosition),
                m_tempoMap.getSamplesPerBeat(),
                &m_tempoMap
            };
            for (const auto& trackPtr : m_tracks) {
                trackPtr->getNextAudioBlock(renderContext);
			}
            m_currentSamplePosition += bufferToFill.numSamples;
        }
		m_voiceEngine.render(bufferToFill);
    }

    MusicSequencer::MusicSequencer(double defaultBpm)
		: m_currentTempoBpm(defaultBpm)
    {
        m_tracks.push_back(std::make_unique<NewMetronomeTrack>(
            m_mediaBay.getMediaBuffer("click", "./Samples/Stick.wav"),
			m_voiceEngine)
        );

        auto audioTrackPtr = std::make_unique<AudioTrack>(
            m_mediaBay.getMediaBuffer("los-chitarros", "./Samples/los-chitarros.wav"),
            m_voiceEngine
		);
		audioTrackPtr->setStartTick(static_cast<std::int64_t>(4 * PPQ)); // start at bar 2


        m_tracks.push_back(std::move(audioTrackPtr));
    }

    void MusicSequencer::uiPlay()
    {
        Command cmd;
        cmd.m_type = CommandType::Play;
        m_commandQueue.pushCommand(cmd);
    }

    void MusicSequencer::uiStop()
    {
        Command cmd;
        cmd.m_type = CommandType::Stop;
        m_commandQueue.pushCommand(cmd);
    }

    void MusicSequencer::uiSetTempo(double bpm)
    {
		m_tempoMap.requestTempo(bpm);
    }
}

