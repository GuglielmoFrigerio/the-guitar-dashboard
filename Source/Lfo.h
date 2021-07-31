#pragma once
#include "IModulationSource.h"

class Lfo : public IModulationSource
{
private:    // fields
    float m_currentRadians = 0.0;
    float m_stepPerSample;

public:
    Lfo(double sampleRate, float frequency);

    float getNext() override;

};

