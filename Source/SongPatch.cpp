/*
  ==============================================================================

    SongPatch.cpp
    Created: 31 Aug 2025 7:10:33pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#include "SongPatch.h"

SongPatch::SongPatch(const juce::XmlElement* pPatchElement, IMidiOutput* pMidiOutput, const int midiChannel)
{
    auto pMidiModifierElement = pPatchElement->getChildByName("MidiModifier");
    if (pMidiModifierElement != nullptr) {
        m_modifierPtr = std::make_unique<MidiModifier>(pMidiModifierElement, pMidiOutput, midiChannel);
    }
}

bool SongPatch::keyPressed(const juce::KeyPress& key) 
{
    if (m_modifierPtr != nullptr)
        return m_modifierPtr->keyPressed(key);
    return false;
}

void SongPatch::start()
{
    if (m_modifierPtr != nullptr)
        m_modifierPtr->start();
}

void SongPatch::end()
{
    if (m_modifierPtr != nullptr)
        m_modifierPtr->end();
}
