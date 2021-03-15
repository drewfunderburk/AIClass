#include "SeePlayerDecision.h"
#include "ComplexEnemy.h"

SeePlayerDecision::SeePlayerDecision(Decision* leftChild, Decision* rightChild, float range, float angle) :
	ABDecision(leftChild, rightChild)
{
	m_range = range;
	m_angle = angle;
}

bool SeePlayerDecision::checkCondition(Agent* agent, float deltaTime)
{
	// Attempt to cast agent as ComplexEnemy
	ComplexEnemy* complexEnemy = dynamic_cast<ComplexEnemy*>(agent);

	// If the cast fails, return false
	if (!agent)
		return false;

	// Return whether the target is both in range and in sight
	return complexEnemy->checkTargetInRange(getRange()) && complexEnemy->checkTargetInSight(getAngle());
}
