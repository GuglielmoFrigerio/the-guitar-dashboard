/*
  ==============================================================================

    GuitarDashCommon.h
    Created: 4 Aug 2021 10:52:16am
    Author:  gugli

  ==============================================================================
*/

#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

const float DoublePi = 2.0f * (float)M_PI;
static const float ReferenceFrequency = 440.0;

int computeSamplesFromMidiNote(int midiNote, double sampleRate);

