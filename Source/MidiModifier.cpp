/*
  ==============================================================================

    MidiModifier.cpp
    Created: 31 Aug 2025 5:23:48pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#include "MidiModifier.h"

void MidiModifier::sendMessage()
{
    int roundedValue = static_cast<int>(std::lround(m_currentValue));
    if (roundedValue != m_lastMidiValue) {
        auto cc = juce::MidiMessage::controllerEvent(m_midiChannel, m_midiControl, roundedValue);
        m_pMidiOutput->addMessage(cc);
        m_pMidiOutput->send();
        m_lastMidiValue = roundedValue;
    }
}

MidiModifier::MidiModifier(const juce::XmlElement* pMidiModifierElement, IMidiOutput* pMidiOutput, const int midiChannel)
    : m_pMidiOutput(pMidiOutput), m_midiChannel(midiChannel)
{
    m_startValue = pMidiModifierElement->getIntAttribute("startValue");
    m_endValue = pMidiModifierElement->getIntAttribute("endValue");

    m_minValue = std::min(m_startValue, m_endValue);
    m_maxValue = std::max(m_startValue, m_endValue);

    m_stepValue = pMidiModifierElement->getIntAttribute("stepValue");
    m_midiControl = pMidiModifierElement->getIntAttribute("midiControl");

    m_currentValue = m_startValue;
}

void MidiModifier::stepUp()
{
    m_currentValue += m_stepValue;
    if (m_currentValue > 127.0)
        m_currentValue = 127.0;

    sendMessage();
}

void MidiModifier::stepDown()
{
    m_currentValue -= m_stepValue;

    if (m_currentValue < 0.0)
        m_currentValue = 0.0;

    sendMessage();
}

bool MidiModifier::keyPressed(const juce::KeyPress& key) 
{
    auto keyCode = key.getKeyCode();
    if (keyCode == 66) {
        stepUp();
        return true;
    }
    return false;
}

void MidiModifier::start() 
{
    m_currentValue = m_startValue;
    sendMessage();
}

void MidiModifier::end()
{
    m_currentValue = m_endValue;
    sendMessage();
}

void MidiModifier::onTick(std::uint64_t currentTick)
{
    auto deltaT = static_cast<std::int64_t>(currentTick) - m_beginTickpoint;
    auto value = deltaT * m_stepValue;
    value = std::max(value, m_minValue);
    value = std::min(value, m_maxValue);

    sendMessage();

    m_lastTick = currentTick;
}

void MidiModifier::onNoteOn(int midiNote)
{
    auto it = m_triggers.find(midiNote);
    if (it != m_triggers.end()) {
        m_beginTickpoint = m_lastTick + it->second.getInitialDelay();
        m_endTickpoint = m_beginTickpoint + it->second.getRampLengthTick();
    }
}
