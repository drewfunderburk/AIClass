#pragma once
#include "ABDecision.h"
class WanderDecision : public ABDecision
{
public:
	using ABDecision::ABDecision;

	virtual void makeDecision(Agent* agent, float deltaTime) override;
};

