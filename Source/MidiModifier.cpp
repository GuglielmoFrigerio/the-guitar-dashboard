/*
  ==============================================================================

    MidiModifier.cpp
    Created: 31 Aug 2025 5:23:48pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#include "MidiModifier.h"

void MidiModifier::setupMinMax()
{
    auto startValue = m_startValue.load();
    auto endValue = m_endValue.load();
    m_minValue = std::min(startValue, endValue);
    m_maxValue = std::max(startValue, endValue);
}

void MidiModifier::sendMessage(double value)
{
    auto actualValue = std::max(value, 0.0);
    actualValue = std::min(actualValue, 127.0);
    m_currentValue = actualValue;
    int roundedValue = static_cast<int>(std::lround(actualValue));
    if (roundedValue != m_lastMidiValue) {
        auto cc = juce::MidiMessage::controllerEvent(m_midiChannel, m_midiControl, roundedValue);
        m_pMidiOutput->addMessage(cc);
        m_pMidiOutput->send();
        m_lastMidiValue = roundedValue;
        DBG("control: " << m_midiControl << " value: " << roundedValue);
    }
}

MidiModifier::MidiModifier(const juce::XmlElement* pMidiModifierElement, IMidiOutput* pMidiOutput, const int midiChannel)
    : m_pMidiOutput(pMidiOutput), m_midiChannel(midiChannel)
{
    m_startValue.store(pMidiModifierElement->getIntAttribute("startValue", -1));
    m_endValue.store(pMidiModifierElement->getIntAttribute("endValue", -1));


    m_stepValue = pMidiModifierElement->getIntAttribute("stepValue");
    m_midiControl = pMidiModifierElement->getIntAttribute("midiControl");

    m_minMidiVelocity = pMidiModifierElement->getIntAttribute("minMidiVelocity", 20);

    setupMinMax();
    m_currentValue = m_startValue.load();

    for (auto* pTriggerElement : pMidiModifierElement->getChildWithTagNameIterator("Trigger")) {
        auto triggerMidiNote = pTriggerElement->getIntAttribute("midiTriggerNote");
        m_triggers.emplace(triggerMidiNote, MidiModifierTrigger(pTriggerElement));
    }
}

void MidiModifier::stepUp()
{
    sendMessage(m_currentValue + m_stepValue);
}

void MidiModifier::stepDown()
{
    sendMessage(m_currentValue - m_stepValue);
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
    m_beginTickpoint.store(0ll);
    auto startValue = m_startValue.load();
    if (startValue >= 0.0) {
        sendMessage(startValue);
    }
}

void MidiModifier::end()
{
    m_beginTickpoint.store(0ll);
    auto endValue = m_endValue.load();
    if (endValue >= 0.0) {
        sendMessage(endValue);
    }
}

void MidiModifier::onTick(std::int64_t microSeconds)
{
    if (m_beginTickpoint.load() > 0ll) {
        auto deltaT = static_cast<std::int64_t>(microSeconds) - m_beginTickpoint;
        auto value = deltaT * m_stepValue;
        value = std::max(value, m_minValue.load());
        value = std::min(value, m_maxValue.load());

        sendMessage(value);
    }

    m_lastTick = microSeconds;
}

void MidiModifier::onNoteOn(int midiNote, int velocity)
{
    if (velocity >= m_minMidiVelocity) {
        auto it = m_triggers.find(midiNote);
        if (it != m_triggers.end()) {
            m_beginTickpoint.store(m_lastTick + it->second.getInitialDelay());
            m_endTickpoint = m_beginTickpoint + it->second.getRampLengthTick();
            m_startValue.store(it->second.getStartValue());
            m_endValue.store(it->second.getEndValue());
            m_stepValue.store(it->second.getStepValue());
            setupMinMax();
        }
    }
}
