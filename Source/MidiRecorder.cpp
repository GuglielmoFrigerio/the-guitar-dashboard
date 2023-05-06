/*
  ==============================================================================

    MidiRecorder.cpp
    Created: 29 Apr 2023 1:08:48pm
    Author:  gugli

  ==============================================================================
*/
#include <stdio.h>
#include <time.h>
#include "MidiRecorder.h"
#include "GuitarDashCommon.h"

MidiRecorder::MidiRecorder(PlaybackEngine* pPlaybackEngine, const juce::String& resourcePath)
    : m_pPlaybackEngine(pPlaybackEngine)
{
    auto resourceRoot = juce::File::getCurrentWorkingDirectory().getChildFile(resourcePath);

    m_recordFolder = resourceRoot.getChildFile("recordings/midi");
    m_recordFolder.createDirectory();
    
}

void MidiRecorder::addQuarterNote(int noteNumber, juce::MidiMessageSequence& midiMessageSequence)
{
    auto noteOnMsg = juce::MidiMessage::noteOn(1, noteNumber, juce::uint8(127));
    midiMessageSequence.addEvent(noteOnMsg, m_currentClick);
    auto noteOffMsg = juce::MidiMessage::noteOff(1, noteNumber, juce::uint8(0));
    m_currentClick += double(DefaultClicksPerBeat);
    midiMessageSequence.addEvent(noteOffMsg, m_currentClick);
}

void MidiRecorder::handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message)
{
    auto currentClick = m_pPlaybackEngine->getCurrentClick();
    m_midiMessageSequence.addEvent(message, (double)currentClick);
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
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%Y.%m.%d_%H_%M_%S.mid", timeinfo);
    return m_recordFolder.getChildFile(buffer);
}

void MidiRecorder::saveFile()
{
    if (m_midiMessageSequence.getNumEvents() > 0) {
        auto midiFilePtr = std::make_unique<juce::MidiFile>();
        midiFilePtr->setTicksPerQuarterNote(DefaultClicksPerBeat);

        midiFilePtr->addTrack(m_midiMessageSequence);

        auto outputFile = getFilename();

        juce::FileOutputStream fos(outputFile);

        midiFilePtr->writeTo(fos);
    }
}
