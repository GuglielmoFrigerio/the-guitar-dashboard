/*
  ==============================================================================

    AutomationTrack.h
    Created: 18 Dec 2022 5:10:28pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "IAutomationTarget.h"
#include "Track.h"

class AutomationTrack : public Track {
public:
    AutomationTrack(const juce::XmlElement* pPatchesElement, IAutomationTarget* pAutomationTarget);

};
