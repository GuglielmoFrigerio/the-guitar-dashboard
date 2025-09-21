/*
  ==============================================================================

    MidiModifierTrigger.cpp
    Created: 20 Sep 2025 4:45:34pm
    Author:  gugli

  ==============================================================================
*/

#include "MidiModifierTrigger.h"

MidiModifierTrigger::MidiModifierTrigger(const juce::XmlElement* pTriggerElement)
{
    m_startValue = pTriggerElement->getIntAttribute("startValue");
    m_endValue = pTriggerElement->getIntAttribute("endValue");

    m_minValue = std::min(m_startValue, m_endValue);
    m_maxValue = std::max(m_startValue, m_endValue);

    m_stepValue = pTriggerElement->getIntAttribute("stepValue");
    m_midiTriggerNote = pTriggerElement->getIntAttribute("midiTriggerNote");
    m_initialDelay = pTriggerElement->getIntAttribute("initialDelayTick");
    m_rampLengthTick = pTriggerElement->getIntAttribute("rampLengthTick");
    if (m_midiTriggerNote > 0 and m_rampLengthTick > 0) {
        m_stepValue = static_cast<double>((m_endValue - m_startValue) / m_rampLengthTick);
    }
}
