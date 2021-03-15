#include "Bullet.h"
#include "Game.h"
#include "Player.h"
#include "Character.h"
Bullet::Bullet(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, MathLibrary::Vector2 velocity) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
	setVelocity(velocity);
}

void Bullet::update(float deltaTime)
{
	Actor::update(deltaTime);

	if (getWorldPosition().x < 0 || getWorldPosition().x > 50
		|| getWorldPosition().y < 0 || getWorldPosition().y > 30)
		Game::destroy(this);

}

void Bullet::onCollision(Actor* other)
{
	Character* character = dynamic_cast<Character*>(other);
	Player* player = dynamic_cast<Player*>(other);

	if (!player && other != this)
	{
		if (character)
			character->takeDamage(1);
		else
			Game::destroy(other);
		Game::destroy(this);
	}
}
