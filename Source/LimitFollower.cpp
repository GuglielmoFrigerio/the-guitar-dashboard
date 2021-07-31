#include "LimitFollower.h"

void LimitFollower::update(const float* pBuffer, int sampleCount)
{
	for (auto index = 0; index < sampleCount; ++index)
	{
		auto sample = pBuffer[index];

		if (sample > m_higher)
			m_higher = sample;

		if (sample < m_lower)
			m_lower = sample;
	}
}

void LimitFollower::reset()
{
	m_lower = std::numeric_limits<float>::max();
	m_higher = std::numeric_limits<float>::lowest();
}

float LimitFollower::getLower()
{
	return (m_lower == std::numeric_limits<float>::max()) ? 0.0 : m_lower;
}

float LimitFollower::getHigher()
{
	return (m_higher == std::numeric_limits<float>::lowest()) ? 0.0 : m_higher;
}
