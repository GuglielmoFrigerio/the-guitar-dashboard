/*
  ==============================================================================

    ValueAnimator.h
    Created: 10 Sep 2021 7:03:06pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ValueAnimator 
{
private:
    int m_startValue;
    int m_endValue;
    int m_steps;
    float m_delta;
    float m_currentInputValue;
    int m_currentOutputValue;
    float m_m;  // y = mx + q
    float m_q;
    int m_currentStep;

public:
    ValueAnimator(int startValue, int endValue, int steps);

    std::function<void(int)> onNewValue;

    bool timerCallback();

    int getCurrentValue() const {
        return static_cast<int>(m_currentOutputValue);
    }

};
