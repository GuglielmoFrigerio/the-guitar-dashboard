#pragma once

class IModulationSource
{
public:
	virtual float getNext() = 0;
	virtual ~IModulationSource()
	{
	}
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
