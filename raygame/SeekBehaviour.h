#pragma once
#include "SteeringBehaviour.h"
class SeekBehaviour : public SteeringBehaviour
{
public:
	SeekBehaviour() { m_target = nullptr; }
	SeekBehaviour(Agent* target) { m_target = target; }

	void update(Agent* agent, float deltaTime) override;
	MathLibrary::Vector2 calculateForce(Agent* agent) override;

	Agent* getTarget() { return m_target; }
	void setTarget(Agent* target) { m_target = target; }

private:
	// Agent the behaviour is seeking
	Agent* m_target;
};

