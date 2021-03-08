#include "SeekBehaviour.h"
#include "Agent.h"

SeekBehaviour::SeekBehaviour()
{
	m_target = nullptr;
	setForceScale(1);
}

SeekBehaviour::SeekBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(seekForce);
}

void SeekBehaviour::update(Agent* agent, float deltaTime)
{
	// Check if agent is null
	if (!agent)
		return;

	// Calculate new force and add it to agent
	agent->addForce(calculateForce(agent));
}

MathLibrary::Vector2 SeekBehaviour::calculateForce(Agent* agent)
{
	// Find the direction to move
	MathLibrary::Vector2 direction = (m_target->getWorldPosition() - agent->getWorldPosition()).getNormalized();

	// Scale the direction vector by seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();

	// Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}
