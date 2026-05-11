/*
  ==============================================================================

    IMidiInputTarget.h
    Created: 30 Dec 2022 7:24:40pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <cstdint>

class IMidiInputTarget {
public:
    virtual ~IMidiInputTarget() {}

    virtual void onNoteOn(int channel, int noteNumber, std::uint8_t velocity) = 0;
};
