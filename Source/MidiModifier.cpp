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
    auto cc = juce::MidiMessage::controllerEvent(m_midiChannel, m_midiControl, m_currentValue);
    m_pMidiOutput->addMessage(cc);
    m_pMidiOutput->send();
}

MidiModifier::MidiModifier(const juce::XmlElement* pMidiModifierElement, IMidiOutput* pMidiOutput, const int midiChannel)
    : m_pMidiOutput(pMidiOutput), m_midiChannel(midiChannel)
{
    m_startValue = pMidiModifierElement->getIntAttribute("startValue");
    m_endValue = pMidiModifierElement->getIntAttribute("endValue");
    m_stepValue = pMidiModifierElement->getIntAttribute("stepValue");
    m_midiControl = pMidiModifierElement->getIntAttribute("midiControl");
    m_currentValue = m_startValue;
}

void MidiModifier::stepUp()
{
    m_currentValue += m_stepValue;
    if (m_currentValue > 127)
        m_currentValue = 127;

    sendMessage();
}

void MidiModifier::stepDown()
{
    m_currentValue -= m_stepValue;

    if (m_currentValue < 0)
        m_currentValue = 0;

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
