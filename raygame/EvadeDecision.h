#pragma once
#include "ABDecision.h"
class EvadeDecision : public ABDecision
{
public:
	using ABDecision::ABDecision;

	virtual void makeDecision(Agent* agent, float deltaTime) override;
};

