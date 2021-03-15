#pragma once
#include "ABDecision.h"
class SeePlayerDecision : public ABDecision
{
public:
	SeePlayerDecision(Decision* leftChild = nullptr, Decision* rightChild = nullptr, float range = 100, float angle = 1);

	virtual bool checkCondition(Agent* agent, float deltaTime) override;

	float getRange() { return m_range; }
	void setRange(float range) { m_range = range; }
	float getAngle() { return m_angle; }
	void setAngle(float angle) { m_angle = angle; }
private:
	float m_range;
	float m_angle;
};

