/*
  ==============================================================================

    MidiRecorder.cpp
    Created: 29 Apr 2023 1:08:48pm
    Author:  gugli

  ==============================================================================
*/

#include "MidiRecorder.h"
#include "GuitarDashCommon.h"

MidiRecorder::MidiRecorder(PlaybackEngine* pPlaybackEngine)
    : m_pPlaybackEngine(pPlaybackEngine)
{
    
}

void MidiRecorder::addQuarterNote(int noteNumber, juce::MidiMessageSequence& midiMessageSequence)
{
    auto noteOnMsg = juce::MidiMessage::noteOn(1, noteNumber, juce::uint8(127));
    midiMessageSequence.addEvent(noteOnMsg, m_currentClick);
    auto noteOffMsg = juce::MidiMessage::noteOff(1, noteNumber, juce::uint8(0));
    m_currentClick += double(DefaultClicksPerBeat);
    midiMessageSequence.addEvent(noteOffMsg, m_currentClick);
}

void MidiRecorder::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    auto currentClick = m_pPlaybackEngine->getCurrentClick();
    m_midiMessageSequence.addEvent(message, currentClick);
}

void MidiRecorder::test()
{
    auto midiFilePtr = std::make_unique<juce::MidiFile>();
    midiFilePtr->setTicksPerQuarterNote(DefaultClicksPerBeat);

    juce::MidiMessageSequence mms;

    for (int noteNumber = 48; noteNumber < 55; noteNumber++) {
        addQuarterNote(noteNumber, mms);
    }

    midiFilePtr->addTrack(mms);

    auto outputFile = juce::File::getCurrentWorkingDirectory().getChildFile("./example.mid");

    juce::FileOutputStream fos(outputFile);

    midiFilePtr->writeTo(fos);
}

juce::File MidiRecorder::getFilename()
{
    return juce::File::getCurrentWorkingDirectory().getChildFile("./example.mid");
}

void MidiRecorder::saveFile()
{
    auto midiFilePtr = std::make_unique<juce::MidiFile>();
    midiFilePtr->setTicksPerQuarterNote(DefaultClicksPerBeat);

    midiFilePtr->addTrack(m_midiMessageSequence);

    auto outputFile = getFilename();

    juce::FileOutputStream fos(outputFile);

    midiFilePtr->writeTo(fos);
}
