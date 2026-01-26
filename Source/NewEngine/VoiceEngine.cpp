/*
  ==============================================================================

    VoiceEngine.cpp
    Created: 18 Jan 2026 4:43:50pm
    Author:  gugli

  ==============================================================================
*/

#include "VoiceEngine.h"

namespace ne
{
    void VoiceEngine::startVoice(const SampleTrigger& t) noexcept
    {
        // Find a free voice, otherwise steal the oldest (simple policy)
        int voiceIndex = -1;
        for (int i = 0; i < MaxVoices; ++i)
            if (!m_voices[i].active()) { voiceIndex = i; break; }

        if (voiceIndex < 0)
            voiceIndex = 0; // voice stealing policy (you can do better later)

        m_voices[voiceIndex].m_sample = t.m_sample;
        m_voices[voiceIndex].m_pos = 0;
        m_voices[voiceIndex].m_gain = t.m_gain;
        m_voices[voiceIndex].m_startDelay = juce::jmax(0, t.m_startOffsetInBlock);
    }

    void VoiceEngine::mixVoices(const juce::AudioSourceChannelInfo& info) noexcept
    {
        auto& out = *info.buffer;
        const int num = info.numSamples;
        const int dstCh = out.getNumChannels();

        for (int v = 0; v < MaxVoices; ++v)
        {
            auto& voice = m_voices[v];
            if (!voice.active())
                continue;

            const auto* s = voice.m_sample;
            const int srcCh = s->getNumChannels();
            const int srcLen = s->getNumSamples();

            int localStart = info.startSample;
            int localNum = num;

            // Apply start offset within the block
            if (voice.m_startDelay > 0)
            {
                const int skip = juce::jmin(voice.m_startDelay, localNum);
                localStart += skip;
                localNum -= skip;
                voice.m_startDelay -= skip;

                if (localNum <= 0)
                    continue; // not started yet in this block
            }

            const int remaining = srcLen - voice.m_pos;
            const int toCopy = juce::jmin(localNum, remaining);

            if (toCopy > 0)
            {
                for (int ch = 0; ch < dstCh; ++ch)
                {
                    out.addFrom(ch, localStart,
                        *s, ch % srcCh, voice.m_pos,
                        toCopy, voice.m_gain);
                }
                voice.m_pos += toCopy;
            }

            if (voice.m_pos >= srcLen)
                voice.stop();
        }
    }

    void VoiceEngine::consumeTriggers() noexcept
    {
        for (;;)
        {
            juce::AbstractFifo::ScopedRead read(m_fifo, 1);
            if (read.blockSize1 == 0)
                break;

            const auto& t = m_triggers[(size_t)read.startIndex1];
            startVoice(t);
        }
    }

    bool VoiceEngine::trigger(const juce::AudioSampleBuffer* sample, int startOffsetInBlock, float gain) noexcept
    {
        if (sample == nullptr) return false;

        juce::AbstractFifo::ScopedWrite write(m_fifo, 1);
        if (write.blockSize1 == 0)
            return false;

        m_triggers[(size_t)write.startIndex1] = { sample, startOffsetInBlock, gain };
        return true;
    }

    void VoiceEngine::render(const juce::AudioSourceChannelInfo& info) noexcept
    {
        // 1) consume triggers and allocate voices
        consumeTriggers();

        // 2) mix voices
        mixVoices(info);
    }
}
