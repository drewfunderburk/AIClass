#include "ComplexEnemy.h"
#include "WanderBehaviour.h"
#include "PursueBehaviour.h"
#include "EvadeBehaviour.h"
#include "Player.h"

void ComplexEnemy::start()
{
	Enemy::start();

	// Init behaviours
	m_wanderBehaviour = getBehaviour<WanderBehaviour>();
	m_pursueBehaviour = getBehaviour<PursueBehaviour>();
	m_evadeBehaviour = getBehaviour<EvadeBehaviour>();

	setTarget(Enemy::getTarget());
}
// Set target to target given from the base class
void ComplexEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_pursueBehaviour->setTarget(target);
	m_evadeBehaviour->setTarget(target);
}

void ComplexEnemy::onCollision(Actor* other)
{
	Enemy::onCollision(other);

	// If the actor is a player, damage it
	Player* player = dynamic_cast<Player*>(other);
	if (!player)
		return;

	player->takeDamage(getDamage());

	// If the target has died, set the target to null
	if (player->getHealth() <= 0)
	{
		setTarget(nullptr);
	}
}

bool ComplexEnemy::checkTargetInSight(float angle)
{
	// Ensure target is not null
	if (!getTarget())
		return false;

	// Get direction to target
	MathLibrary::Vector2 directionToTarget = (getTarget()->getWorldPosition() - getWorldPosition()).getNormalized();

	// Get dotproduct of this enemy's forward vector and the direction
	float dotProduct = MathLibrary::Vector2::dotProduct(getForward(), directionToTarget);

	// Return whether or not the target is within the viewing angle
	return acos(dotProduct) < angle;
}

bool ComplexEnemy::checkTargetInRange(float range)
{
	// Return false if target is null
	if (!getTarget())
		return false;

	// Return whether or not target is within range
	return (getTarget()->getWorldPosition() - getWorldPosition()).getMagnitude() < range;
}
