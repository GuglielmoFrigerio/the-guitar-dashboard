/*
  ==============================================================================

    AverageComputer.h
    Created: 17 Aug 2022 2:45:21pm
    Author:  Guglielmo

  ==============================================================================
*/

#pragma once

template <class T>
class AverageComputer {
private:
    T* m_pArray;
    int m_length;
    int m_count = 0;

public:
    AverageComputer(int sampleCount) {
        m_pArray = new T[sampleCount];
        m_length = sampleCount;
    }

    ~AverageComputer() {
        delete[] m_pArray;
    }

    bool add(T newSample) {
        if (m_count < m_length) {
            m_pArray[m_count] = newSample;
            m_count++;
        }

        return m_count < m_length;
    }

    T getAverage() {
        T sum = (T)0;

        for (int index = 0; index < m_count; index++) {
            sum += m_pArray[index];
        }

        return sum / (T)m_count;
    }
};
