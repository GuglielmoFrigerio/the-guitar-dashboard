/*
  ==============================================================================

    MetronomeTrack.h
    Created: 29 Dec 2022 9:13:16am
    Author:  gugli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Track.h"
#include "VirtualBand.h"

class MetronomeTrack : public Track {
public:
    MetronomeTrack(VirtualBand* pVirtualBand);
};
