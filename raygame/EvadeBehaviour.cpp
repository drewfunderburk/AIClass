#include "EvadeBehaviour.h"
#include "Agent.h"

EvadeBehaviour::EvadeBehaviour()
{
	m_target = nullptr;
	m_seekForce = 1;
}

EvadeBehaviour::EvadeBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	m_seekForce = seekForce;
}

void EvadeBehaviour::update(Agent* agent, float deltaTime)
{
	// Check if agent is null
	if (!agent)
		return;

	// Calculate new force and add it to agent
	agent->addForce(calculateForce(agent));
}

MathLibrary::Vector2 EvadeBehaviour::calculateForce(Agent* agent)
{
	// Find the direction to move
	MathLibrary::Vector2 direction = (agent->getWorldPosition() - (m_target->getWorldPosition() + m_target->getVelocity())).getNormalized();

	// Scale the direction vector by seekForce
	MathLibrary::Vector2 desiredVelocity = direction * m_seekForce;

	// Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}
