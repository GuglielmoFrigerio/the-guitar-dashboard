/*
  ==============================================================================

    TheLambsSong.h
    Created: 21 Aug 2021 7:04:54pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "Song.h"

class VirtualBand;

class TheLambsSong : public Song
{
public:
    TheLambsSong(const juce::XmlElement* pPatchesElement, const VirtualBand* pVirtualBand);

    virtual void activate() override;
};
