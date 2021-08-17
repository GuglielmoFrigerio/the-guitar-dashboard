/*
  ==============================================================================

    ThreadResponse.h
    Created: 17 Aug 2021 3:51:54pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <tuple>
#include <JuceHeader.h>

template <typename T>
class ThreadResponse {
private:
    bool            m_result;
    juce::String    m_reason;
    juce::Thread*   m_pWaitingThread;
    T               m_answerData;

public:
    void prepare()
    {
        m_pWaitingThread = juce::Thread::getCurrentThread();
        jassert(m_pWaitingThread != nullptr);

        m_result = false;
        m_reason.clear();
    }

    std::tuple<bool, juce::String> waitForAnswer(int timeoutMillisecs)
    {
        jassert(m_pWaitingThread != nullptr);
        if (m_pWaitingThread->wait(timeoutMillisecs)) {
            return { m_result, m_reason };
        }
        return { false, "operation timed out." };
    }

    void failOperation(const char* reason)
    {
        jassert(m_pWaitingThread != nullptr);
        m_result = false;
        m_reason = reason;
        m_pWaitingThread->notify();
    }

    void provideAnswer()
    {
        jassert(m_pWaitingThread != nullptr);
        m_result = true;
        m_pWaitingThread->notify();
    }

    T& getAnswerData()
    {
        return m_answerData;
    }
};
