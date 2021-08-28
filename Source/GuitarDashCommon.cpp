/*
  ==============================================================================

    GuitarDashCommon.cpp
    Created: 9 Aug 2021 11:33:52am
    Author:  gugli

  ==============================================================================
*/

#include "GuitarDashCommon.h"

int computeSamplesFromMidiNote(int midiNote, double sampleRate)
{
    auto minimumFrequency = ReferenceFrequency * std::powf(2.0f, ((float)midiNote - 69.0f) / 12.0f);
    return (int)std::round(sampleRate / minimumFrequency);
}

bool stringsAreSimilar(const juce::String& first, const juce::String& second, int comparisonLength, int minimumLength)
{
    auto max = std::min(std::min(comparisonLength, second.length()), first.length());
    for (auto index = 0; index < max; ++index)
    {
        if (first[index] != second[index])
            return false;

    }
    return max >= minimumLength;
}

int getElementValueAsInt(const juce::XmlElement* pInputElement)
{
    auto text = pInputElement->getAllSubText().trim();
    return text.getIntValue();
}

juce::XmlElement* getChildWithAttribute(const juce::XmlElement* pInputElement, juce::StringRef attributeName, juce::StringRef attributeValue)
{
    for (auto* pChildElement : pInputElement->getChildIterator()) {
        auto value = pChildElement->getStringAttribute(attributeName);
        if (value == attributeValue)
        {
            return pChildElement;
        }
    }
    return nullptr;
}

void computeFlexBox(int minWidth, int tileHeight, int componentWidth, int tileCount, std::function<void(int, int, int, int, int)> tileHandler)
{
    auto columns = componentWidth / minWidth;
    auto mod = tileCount % columns;
    auto rows = (tileCount / columns) + ((mod != 0) ? 1 : 0);
    auto tileWidth = componentWidth / columns;

    for (auto rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (auto columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            auto index = rowIndex * columns + columnIndex;
            if (index < tileCount) {
                tileHandler(index, columnIndex * tileWidth, rowIndex * tileHeight, tileWidth, tileHeight);
            }
            else break;
        }
    }
}

