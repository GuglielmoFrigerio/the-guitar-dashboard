/*
  ==============================================================================

    MusicSequencer.cpp
    Created: 31 Dec 2025 10:02:27am
    Author:  gugli

  ==============================================================================
*/

#include "MusicSequencer.h"

namespace ne {
    void MusicSequencer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
        m_samplesPerBlock = samplesPerBlockExpected;
        m_sampleRate = sampleRate;
        m_currentSamplePosition = 0;
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
        // Update current sample position
        if (m_playing)
            m_currentSamplePosition += bufferToFill.numSamples;
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

