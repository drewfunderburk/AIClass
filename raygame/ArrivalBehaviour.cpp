#include "ArrivalBehaviour.h"
#include "Agent.h"

ArrivalBehaviour::ArrivalBehaviour()
{
	m_target = nullptr;
	m_seekForce = 1;
}

ArrivalBehaviour::ArrivalBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	m_seekForce = seekForce;
}

void ArrivalBehaviour::update(Agent* agent, float deltaTime)
{
	// Check if agent is null
	if (!agent)
		return;

	// Calculate new force and add it to agent
	agent->addForce(calculateForce(agent));
}

MathLibrary::Vector2 ArrivalBehaviour::calculateForce(Agent* agent)
{
	// Find the direction to move
	MathLibrary::Vector2 direction = (m_target->getWorldPosition() - agent->getWorldPosition()).getNormalized();

	// Get distance to target
	float distanceToTarget = (m_target->getWorldPosition() - agent->getWorldPosition()).getMagnitude();

	// Scale the direction vector by seekForce
	MathLibrary::Vector2 desiredVelocity;
	float radius = 5;
	if (distanceToTarget > radius)
		desiredVelocity = direction * m_seekForce;
	else
		desiredVelocity = direction * m_seekForce * (distanceToTarget / radius);

	// Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	
	return steeringForce;
}
