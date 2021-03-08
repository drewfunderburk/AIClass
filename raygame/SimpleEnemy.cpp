#include "SimpleEnemy.h"
#include "WanderBehaviour.h"
#include "SeekBehaviour.h"

bool SimpleEnemy::checkTargetInSight()
{
	// Ensure target is not null
	if (!getTarget())
		return false;

	// Viewing angle
	int viewingAngleInRadians = 1;

	// Get direction to target
	MathLibrary::Vector2 directionToTarget = (getTarget()->getWorldPosition() - getWorldPosition()).getNormalized();

	// Get dotproduct of this enemy's forward vector and the direction
	float dotProduct = MathLibrary::Vector2::dotProduct(getForward(), directionToTarget);

	// Return whether or not the target is within the viewing angle
	return acos(dotProduct) < viewingAngleInRadians;
}

void SimpleEnemy::onCollision(Actor* other)
{
	// Check to see if the enemy ran into the player
	if (other = getTarget())
	{
		// If so, deal damage to the player
		
		// If the player health is less tham 0, set the target to be nullptr
	}

}

void SimpleEnemy::start()
{
	// Call base
	Enemy::start();

	// Set default state to wander
	m_currentState = WANDER;

	// Init member variables
	m_seek = getBehaviour<SeekBehaviour>();
	m_wander = getBehaviour<WanderBehaviour>();

	// Set target to base class target
	setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltaTime)
{
	switch (m_currentState)
	{
	case WANDER:
		if (checkTargetInSight())
		{
			m_wander->setForceScale(0);
			m_currentState = SEEK;
		}
		else
			m_wander->setForceScale(1);
		break;
	case SEEK:
		if (!checkTargetInSight())
		{
			m_seek->setForceScale(0);
			m_currentState = WANDER;
		}
		else
			m_seek->setForceScale(1);
		break;
	}

	Enemy::update(deltaTime);
}

void SimpleEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_seek->setTarget(target);
}