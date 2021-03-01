#include "SeekBehaviour.h"
#include "Agent.h"

void SeekBehaviour::update(Agent* agent, float deltaTime)
{
}

MathLibrary::Vector2 SeekBehaviour::calculateForce(Agent* agent)
{
	// Do seek behaviour
	MathLibrary::Vector2 direction = (m_target->getWorldPosition() - agent->getWorldPosition()).getNormalized();
	return MathLibrary::Vector2();
}
