#include "HealthLowDecision.h"
#include "Character.h"

bool HealthLowDecision::checkCondition(Agent* agent, float deltaTime)
{
	// Attempt to cast agent to a Character
	Character* character = dynamic_cast<Character*>(agent);

	// If cast fails, return false
	if (!character)
		return false;

	// Return whether or not the character's health is below the threshold
	return character->getHealth() < getHealthThreshold();
}
