/*
  ==============================================================================

    GuitarDashCommon.h
    Created: 4 Aug 2021 10:52:16am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <functional>
#include <JuceHeader.h>

#define M_PI       3.14159265358979323846   // pi
const float DoublePi = 2.0f * (float)M_PI;
static const float ReferenceFrequency = 440.0;

int computeSamplesFromMidiNote(int midiNote, double sampleRate);

bool stringsAreSimilar(const juce::String& first, const juce::String& second, int comparisonLength, int minimumLength);

int getElementValueAsInt(const juce::XmlElement* pInputElement);

juce::XmlElement* getChildWithAttribute(const juce::XmlElement* pInputElement, juce::StringRef attributeName, juce::StringRef attributeValue);

void computeFlexBox(int minWidth, int tileHeight, int componentWidth, int tileCount, std::function<void(int, int, int, int, int)> tileHandler);

