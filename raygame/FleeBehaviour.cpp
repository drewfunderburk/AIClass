#include "FleeBehaviour.h"
#include "Agent.h"

FleeBehaviour::FleeBehaviour()
{
	m_target = nullptr;
	setForceScale(1);
}

FleeBehaviour::FleeBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(seekForce);
}

void FleeBehaviour::update(Agent* agent, float deltaTime)
{
	// Check if agent is null
	if (!agent)
		return;

	// Calculate new force and add it to agent
	agent->addForce(calculateForce(agent));
}

MathLibrary::Vector2 FleeBehaviour::calculateForce(Agent* agent)
{
	// Find the direction to move
	MathLibrary::Vector2 direction = (agent->getWorldPosition() - m_target->getWorldPosition()).getNormalized();

	// Scale the direction vector by seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();

	// Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}
