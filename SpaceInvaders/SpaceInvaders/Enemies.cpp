#include "Enemies.hpp"

void SimpleEnemy::UpdateEnemy(sf::Time deltaTime)
{
	MoveBy(0, deltaTime.asSeconds() * Speed);
}

void MovingEnemy::UpdateEnemy(sf::Time deltaTime)
{
	MoveBy(MovementX(deltaTime), MovementY(deltaTime));
}

float  MovingEnemy::MovementX(sf::Time deltaTime)
{
	float deltaX;
	if (MovementDirection == Direction::Left)
	{
		deltaX = -HorizontalSpeed * deltaTime.asSeconds();
		if (position.x + deltaX < std::max(0.f + ENEMY_SIZE / 2, OriginalPosition - HorizontalRange)) // TODO number (enemy size)
			MovementDirection = Direction::Right;
	}
	else
	{
		deltaX = HorizontalSpeed * deltaTime.asSeconds();
		if (position.x + deltaX > std::min((float)SCREEN_WIDTH - ENEMY_SIZE / 2, OriginalPosition + HorizontalRange)) // TODO number (enemy size)
			MovementDirection = Direction::Left;
	}
	return deltaX;
}

float MovingEnemy::MovementY(sf::Time deltaTime)
{
	return deltaTime.asSeconds() * Speed;
}

void ShootingEnemy::UpdateEnemy(sf::Time deltaTime)
{
	RocketTimer -= deltaTime.asSeconds();
	MoveBy(MovementX(deltaTime), MovementY(deltaTime));
}

bool ShootingEnemy::ShootRocket()
{
	if (RocketTimer <= 0)
	{
		RocketTimer = GetRocketTime();
		return true;
	}
	return false;
}
