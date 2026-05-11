/*
  ==============================================================================

    MidiMessageFilter.cpp
    Created: 13 Nov 2022 11:25:43am
    Author:  gugli

  ==============================================================================
*/

#include "MidiMessageFilter.h"

MidiMessageFilter::MidiMessageFilter()
    : m_programChangeFilter(16), m_controllerFilters(16)
{
    
}

MidiMessageFilter::ControllerFilter::ControllerFilter()
    :   m_controllerFilters(128)
{
}

bool MidiMessageFilter::ControllerFilter::canSend(const juce::uint8* pRawData)
{
    juce::uint8 controllerIndex = pRawData[1];
    return m_controllerFilters[controllerIndex].canSend(pRawData[2]);
}

void MidiMessageFilter::ControllerFilter::reset()
{
    for (auto& parameterFilter : m_controllerFilters)
        parameterFilter.reset();
}
