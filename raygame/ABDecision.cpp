#include "ABDecision.h"

ABDecision::ABDecision(Decision* leftChild, Decision* rightChild)
{
	m_leftChild = leftChild;
	m_rightChild = rightChild;
}

void ABDecision::makeDecision(Agent* agent, float deltaTime)
{
	// Call the check condition function for this decision
	if (checkCondition(agent, deltaTime))
	{
		// If the condition returns true and the child isn't null,
		// move to the left node
		if (m_leftChild)
			m_leftChild->makeDecision(agent, deltaTime);
	}
	else
	{
		// If the condition returns false and the right child isn't null,
		// move to the right
		if (m_rightChild)
			m_rightChild->makeDecision(agent, deltaTime);
	}
}
