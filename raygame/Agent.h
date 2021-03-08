#pragma once
#include "Actor.h"
#include <vector>

class Behaviour;

class Agent : public Actor
{
public:
	Agent();
	~Agent();

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name="maxForce">The largest the magnitude of the force vector can be</param>
    Agent(float x, float y, float collisionRadius, char icon, float maxSpeed, float maxForce);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name="maxForce">The largest the magnitude of the force vector can be</param>
    Agent(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed, float maxForce);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name="maxForce">The largest the magnitude of the force vector can be</param>
    Agent(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float maxForce);

    void update(float deltaTime) override;

    // Add the given force to the total force being applied to the agent.
    void addForce(MathLibrary::Vector2 force);
    void addBehaviour(Behaviour* behaviour);

    float getMaxForce() { return m_maxForce; }
    void setMaxForce(float maxForce) { m_maxForce = maxForce; }

    template<typename BehaviourType>
    /// <summary>
    /// Returns the first behaviour that matches the given type.
    /// If no behaviour matches the type, returns nullptr
    /// </summary>
    BehaviourType* getBehaviour();

private:
	MathLibrary::Vector2 m_force;
	float m_maxForce;
	std::vector<Behaviour*> m_behaviours;
};

template<typename BehaviourType>
inline BehaviourType* Agent::getBehaviour()
{
    // Iterate through list of behaviours
    for (int i = 0; i < m_behaviours.size(); i++)
    {
        // Attempt to cast a behaviour to the given type
        BehaviourType* behaviour = dynamic_cast<BehaviourType*>(m_behaviours[i]);

        // If the cast was successful, return the behaviour
        if (behaviour)
            return behaviour;
    }

    // If no behaviour of that type was found, return null
    return nullptr;
}
