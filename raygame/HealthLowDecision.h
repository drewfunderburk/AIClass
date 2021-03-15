#pragma once
#include "ABDecision.h"
class HealthLowDecision :
	public ABDecision
{
public:
	HealthLowDecision(Decision* m_leftChild = nullptr, Decision* m_rightChild = nullptr, float healthThreshold = 1) :
		ABDecision(m_leftChild, m_rightChild) { m_healthThreshold = healthThreshold; }

	virtual bool checkCondition(Agent* agent, float deltaTime) override;

	float getHealthThreshold() { return m_healthThreshold; }
	void setHealthThreshold(float healthThreshold) { m_healthThreshold = healthThreshold; }

private:
	float m_healthThreshold;
};

