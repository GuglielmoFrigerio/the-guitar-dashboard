#pragma once

#include <limits>

class LimitFollower
{
private:
	float m_lower = std::numeric_limits<float>::max();
	float m_higher = std::numeric_limits<float>::lowest();

public:
	void update(const float* pBuffer, int sampleCount);
	void reset();

	float getLower();
	float getHigher();
};

