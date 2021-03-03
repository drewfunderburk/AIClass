#pragma once
#include "Agent.h"
class Enemy : public Agent
{
public:
	Enemy();
	Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, Agent* target, float maxSpeed, float maxForce);

	void update(float deltaTime) override;

	void setTarget(Agent* agent) { m_target = agent; }

private:
	Agent* m_target;
};

