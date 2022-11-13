/*
  ==============================================================================

    MidiMessageFilter.h
    Created: 13 Nov 2022 11:25:43am
    Author:  gugli

  ==============================================================================
*/

#include <JuceHeader.h>
#include <vector>

#pragma once

class MidiMessageFilter {
private:
    class ParameterFiter {
    private:
        int m_lastValue = -1;

    public:
        bool canSend(juce::uint8 newValue) {
            int newValueAsInt = newValue;
            auto returnValue = newValueAsInt != m_lastValue;
            m_lastValue = newValueAsInt;
            return returnValue;
        }
    };

    class ControllerFilter
    {
    private:
        std::vector<ParameterFiter> m_controllerFilters;

    public:
        ControllerFilter();

        bool canSend(const juce::uint8* pRawData);
    };
   
    std::vector<ParameterFiter> m_programChangeFilter;
    std::vector<ControllerFilter> m_controllerFilters;

public:
    MidiMessageFilter();
    bool isProgramChange(juce::uint8 value) const {
        return (value & 0xf0) == 192;
    }

    bool isControlChange(juce::uint8 value) const {
        return (value & 0xf0) == 176;
    }

    bool canSendMessage(const juce::MidiMessage& midiMessage)
    {
        auto rawData = midiMessage.getRawData();
        auto channelZeroBased = midiMessage.getChannel() - 1;
        if (isProgramChange(*rawData)) {
            return m_programChangeFilter[channelZeroBased].canSend(rawData[1]);

        }
        else if (isControlChange(*rawData)) {
            return m_controllerFilters[channelZeroBased].canSend(rawData);
        }
        return true;
    }
};
