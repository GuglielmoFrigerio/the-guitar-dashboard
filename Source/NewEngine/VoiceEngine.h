/*
  ==============================================================================

    VoiceEngine.h
    Created: 18 Jan 2026 4:43:50pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace ne
{
    struct SampleTrigger
    {
        const juce::AudioSampleBuffer* m_sample = nullptr; // non-owning, must stay valid
        int m_startOffsetInBlock = 0;                      // 0..numSamples-1
        float m_gain = 1.0f;
    };

    struct Voice
    {
        const juce::AudioSampleBuffer* m_sample = nullptr;
        int m_pos = 0;           // read position in sample buffer
        float m_gain = 1.0f;
        int m_startDelay = 0;    // samples to wait before starting in this block (offset)

        bool active() const noexcept { return m_sample != nullptr; }
        void stop() noexcept { m_sample = nullptr; m_pos = 0; m_startDelay = 0; }
    };

    class VoiceEngine
    {
    public:
        static constexpr int MaxVoices = 32;
        static constexpr int TriggerFifoSize = 128;

    private:
        juce::AbstractFifo m_fifo;
        std::array<SampleTrigger, TriggerFifoSize> m_triggers{};
        std::array<Voice, MaxVoices> m_voices{};

    private:

        void startVoice(const SampleTrigger& t) noexcept;

        void mixVoices(const juce::AudioSourceChannelInfo& info) noexcept;

        void consumeTriggers() noexcept;

    public:
        VoiceEngine()
            : m_fifo(TriggerFifoSize)
        {
        }
        ~VoiceEngine() = default;

        bool trigger(const juce::AudioSampleBuffer* sample, int startOffsetInBlock, float gain) noexcept;

        void render(const juce::AudioSourceChannelInfo& info) noexcept;
    };
}
