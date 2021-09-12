/*
  ==============================================================================

    ValueAnimator.cpp
    Created: 10 Sep 2021 7:03:06pm
    Author:  gugli

  ==============================================================================
*/

#include <math.h>
#include "ValueAnimator.h"
#include "GuitarDashCommon.h"

ValueAnimator::ValueAnimator(int startValue, int endValue, int steps)
    :   m_startValue(startValue), m_endValue(endValue), m_steps(steps), m_currentOutputValue(startValue), m_currentStep(0)
{
    m_delta = M_PI / static_cast<float>(m_steps);
    m_currentInputValue = M_PI;
    m_m = static_cast<float>(m_endValue - m_startValue) / 2.0f;
    m_q = static_cast<float>(m_startValue) + m_m;
}

bool ValueAnimator::timerCallback()
{
    m_currentInputValue += m_delta;
    auto outputValue = static_cast<int>(cos(m_currentInputValue) * m_m + m_q);
    if (outputValue != m_currentOutputValue) {
        m_currentOutputValue = outputValue;
        if (onNewValue != nullptr)
            onNewValue(static_cast<int>(m_currentOutputValue));
    }
    m_currentStep++;
    return m_currentStep < m_steps;
}
