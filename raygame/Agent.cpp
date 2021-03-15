#include "Agent.h"
#include "Behaviour.h"

Agent::Agent() : Actor()
{
	m_force = { 0, 0 };
	m_maxForce = 1;
}

Agent::~Agent()
{
}

Agent::Agent(float x, float y, float collisionRadius, char icon, float maxSpeed = 1, float maxForce = 1) :
	Actor(x, y, collisionRadius, icon, maxSpeed)
{
	m_force = { 0, 0 };
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed = 1, float maxForce = 1) :
	Actor(x, y, collisionRadius, sprite, maxSpeed)
{
	m_force = { 0, 0 };
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed = 1, float maxForce = 1) :
	Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
	m_force = { 0, 0 };
	m_maxForce = maxForce;
}

void Agent::update(float deltaTime)
{
	// Reset force
	m_force = { 0, 0 };

	// Call update for each behaviour
	for (int i = 0; i < m_behaviours.size(); i++)
	{
		if (m_behaviours[i]->getEnabled())
			m_behaviours[i]->update(this, deltaTime);
	}

	// Update velocity with the new force
	setVelocity(getVelocity() + m_force * deltaTime);

	// Rotates the agent to face the direction it's moving in
	updateFacing();

	Actor::update(deltaTime);
}

void Agent::addForce(MathLibrary::Vector2 force)
{
	// Add the force given to total force
	m_force = m_force + force;

	// Clamp to getMaxForce()
	if (m_force.getMagnitude() > getMaxForce())
		m_force = m_force.getNormalized() * getMaxForce();
}

void Agent::addBehaviour(Behaviour* behaviour)
{
	if (behaviour)
		m_behaviours.push_back(behaviour);
}
