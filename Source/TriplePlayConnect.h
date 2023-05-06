/*
  ==============================================================================

    TriplePlayConnect.h
    Created: 30 Dec 2022 7:25:26pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <memory>
#include "IMidiInputTarget.h"

class TriplePlayConnect : public juce::MidiInputCallback {
private:
    IMidiInputTarget* m_pMidiInputTarget;
    std::unique_ptr<juce::MidiInput> m_midiInputPtr;
    std::atomic<std::shared_ptr<juce::MidiInputCallback>> m_midiInputCallbackPtr;

private:
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;

public:
    TriplePlayConnect(IMidiInputTarget* pMidiInputTarget);
    ~TriplePlayConnect();

    std::function<void(int)> onSongSelect;

    void setMidiInputCallback(std::shared_ptr<juce::MidiInputCallback>& midiInputCallbackPtr);
    void clearMidiInputCallback();
};
