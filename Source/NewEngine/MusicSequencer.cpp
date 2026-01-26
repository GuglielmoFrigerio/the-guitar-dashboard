/*
  ==============================================================================

    MusicSequencer.cpp
    Created: 31 Dec 2025 10:02:27am
    Author:  gugli

  ==============================================================================
*/

#include "MusicSequencer.h"
#include "NewMetronomeTrack.h"

namespace ne {

    void MusicSequencer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
        m_samplesPerBlock = samplesPerBlockExpected;
        m_sampleRate = sampleRate;
        m_currentSamplePosition = 0;
		m_tempoMap.prepareToPlay(samplesPerBlockExpected, sampleRate);
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
        if (m_playing) {
            RenderContext renderContext {
                bufferToFill,
                m_currentSamplePosition,
                m_currentSamplePosition + bufferToFill.numSamples,
                m_tempoMap.samplesToTicks(m_currentSamplePosition)
			};
            for (const auto& trackPtr : m_tracks) {
                trackPtr->getNextAudioBlock(renderContext);
			}
            m_currentSamplePosition += bufferToFill.numSamples;
        }
    }

    MusicSequencer::MusicSequencer()
    {
        m_tracks.push_back(std::make_unique<NewMetronomeTrack>(
            m_mediaBay.getMediaBuffer("click", juce::File("./Resources/Samples/Stick.wav")),
			m_voiceEngine)
        );
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
}

