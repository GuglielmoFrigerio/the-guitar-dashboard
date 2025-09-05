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
