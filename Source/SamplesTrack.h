/*
  ==============================================================================

    SamplesTrack.h
    Created: 11 Dec 2022 7:12:03pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Track.h"
#include "VirtualBand.h"

class SamplesTrack : public Track {
public:
    SamplesTrack(const juce::XmlElement* pSamplesElement, VirtualBand* pVirtualBand, const juce::String& resourcesPath);
};
