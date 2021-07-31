//
//  Oscillator.hpp
//  SimpleEQ
//
//  Created by Guglielmo Frigerio on 07/07/21.
//

#pragma once

class Oscillator {
private:    // fields
    float m_currentRadians = 0.0;
    float m_stepPerSample;

public:
    Oscillator(double sampleRate, float frequency);
    
    void play(float* pBuffer, int bufferLength, float volume);    
    
};
