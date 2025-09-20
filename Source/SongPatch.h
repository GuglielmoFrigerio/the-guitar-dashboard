/*
  ==============================================================================

    SongPatch.h
    Created: 31 Aug 2025 7:10:33pm
    Author:  frigeriog-adm

  ==============================================================================
*/

#pragma once
#include "MidiModifier.h"

class SongPatch {
private:
    std::shared_ptr<MidiModifier> m_modifierPtr;

public:
    SongPatch(const juce::XmlElement* pPatchElement, IMidiOutput* pMidiOutput, const int midiChannel);

    bool keyPressed(const juce::KeyPress& key);
    void start();
    void end();

    int getCurrentModifierValue() const {
        if (m_modifierPtr != nullptr)
            return m_modifierPtr->getCurrentValue();
        return -1;
    }

    inline void onTick(std::uint64_t currentTick) {
        if (m_modifierPtr != nullptr)
            m_modifierPtr->onTick(currentTick);
    }

    inline void onNoteOn(int noteNumber) {
        if (m_modifierPtr != nullptr)
            m_modifierPtr->onNoteOn(noteNumber);
    }
};
