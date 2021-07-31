#pragma once

class IModulationSource
{
public:
	virtual float getNext() = 0;
};

struct FixedModulation : public IModulationSource
{
private:
	float m_value;

public:
	FixedModulation(float value) : m_value(value) {}

	virtual float getNext() override {
		return m_value;
	}

};
