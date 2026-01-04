/*
  ==============================================================================

    CommandQueue.h
    Created: 31 Dec 2025 12:34:48pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <cstdint>
#include <array>
#include <JuceHeader.h>

namespace ne {
    const int MaxPendingCommands = 128;


    enum class CommandType : std::uint8_t { Play, Stop, SetBpm, SeekSamples };

    struct Command
    {
        CommandType m_type;
        union {
            double m_bpm;
            std::int64_t  m_samplePosition;
        };
    };


    class CommandQueue {
    private:
        juce::AbstractFifo m_commandFifo{ MaxPendingCommands };
        std::array<Command, MaxPendingCommands> m_commands;

    public:
        CommandQueue() = default;
        ~CommandQueue() = default;

        void pushCommand(const Command& cmd);

        bool popCommand(Command& cmd);
    };
}


