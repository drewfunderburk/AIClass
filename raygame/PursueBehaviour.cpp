#include "PursueBehaviour.h"
#include "Agent.h"

PursueBehaviour::PursueBehaviour()
{
	m_target = nullptr;
	m_seekForce = 1;
}

PursueBehaviour::PursueBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	m_seekForce = seekForce;
}

void PursueBehaviour::update(Agent* agent, float deltaTime)
{
	// Check if agent is null
	if (!agent)
		return;

	// Calculate new force and add it to agent
	agent->addForce(calculateForce(agent));
}

MathLibrary::Vector2 PursueBehaviour::calculateForce(Agent* agent)
{
	// Find the direction to move
	MathLibrary::Vector2 direction = ((m_target->getWorldPosition() + m_target->getVelocity()) - agent->getWorldPosition()).getNormalized();

	// Scale the direction vector by seekForce
	MathLibrary::Vector2 desiredVelocity = direction * m_seekForce;

	// Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}
