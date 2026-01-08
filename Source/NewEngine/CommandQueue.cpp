/*
  ==============================================================================

    CommandQueue.cpp
    Created: 31 Dec 2025 12:34:48pm
    Author:  gugli

  ==============================================================================
*/

#include "CommandQueue.h"

namespace ne {
    void CommandQueue::pushCommand(const Command& cmd)
    {
        auto writeHandle = m_commandFifo.write(1);
        if (writeHandle.blockSize1 > 0)
        {
            m_commands[writeHandle.startIndex1] = cmd;
        }
        else
        {
            jassertfalse; // FIFO full, should not happen if used correctly
        }
    }

    bool CommandQueue::popCommand(Command& cmd)
    {
        auto readHandle = m_commandFifo.read(1);
        if (readHandle.blockSize1 > 0)
        {
            cmd = m_commands[readHandle.startIndex1];
            return true;
        }
        return false;
    }
}

