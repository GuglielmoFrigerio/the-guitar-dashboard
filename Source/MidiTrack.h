/*
  ==============================================================================

    MidiTrack.h
    Created: 14 Aug 2021 9:52:21am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include "Track.h"

class MidiTrack : public Track
{
private:
    int     m_midiChannel = 1;

};
