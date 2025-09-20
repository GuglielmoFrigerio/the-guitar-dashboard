/*
  ==============================================================================

    MidiModifierTrigger.cpp
    Created: 20 Sep 2025 4:45:34pm
    Author:  gugli

  ==============================================================================
*/

#include "MidiModifierTrigger.h"

MidiModifierTrigger::MidiModifierTrigger(const juce::XmlElement* pMidiModifierElement)
{
    m_startValue = pMidiModifierElement->getIntAttribute("startValue");
    m_endValue = pMidiModifierElement->getIntAttribute("endValue");

    m_minValue = std::min(m_startValue, m_endValue);
    m_maxValue = std::max(m_startValue, m_endValue);

    m_stepValue = pMidiModifierElement->getIntAttribute("stepValue");
    m_midiTriggerNote = pMidiModifierElement->getIntAttribute("midiTriggerNote");
    m_initialDelay = pMidiModifierElement->getIntAttribute("initialDelayTick");
    m_rampLengthTick = pMidiModifierElement->getIntAttribute("rampLengthTick");
    if (m_midiTriggerNote > 0 and m_rampLengthTick > 0) {
        m_stepValue = static_cast<double>((m_endValue - m_startValue) / m_rampLengthTick);
    }
}
