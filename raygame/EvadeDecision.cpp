#include "EvadeDecision.h"
#include "ComplexEnemy.h"
#include "WanderBehaviour.h"
#include "PursueBehaviour.h"
#include "EvadeBehaviour.h"

void EvadeDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (!enemy)
		return;

	enemy->getPursue()->setEnabled(false);
	enemy->getWander()->setEnabled(false);
	enemy->getEvade()->setEnabled(true);
}
