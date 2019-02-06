#include "Enemies.hpp"

void SimpleEnemy::Update(sf::Time deltaTime)
{
	MoveBy(0, deltaTime.asSeconds() * Speed);

	if (GetPosition().y > SCREEN_HEIGHT + ENEMY_SIZE)
		RemoveEnemy();
}

void MovingEnemy::Update(sf::Time deltaTime)
{
	MoveBy(MovementX(deltaTime), MovementY(deltaTime));

	if (GetPosition().y > SCREEN_HEIGHT + ENEMY_SIZE)
		RemoveEnemy();
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

void ShootingEnemy::Update(sf::Time deltaTime)
{
	RocketTimer -= deltaTime.asSeconds();
	if (RocketTimer <= 0)
	{
		RocketTimer = GetRocketTime();
		std::unique_ptr<EnemyRocket> r = std::make_unique<EnemyRocket>(ROCKET_SPEED);
		r->SetPosition(GetPosition());
		GameObjectManager::getInstance().AddGameObject(std::move(r));
	}

	MoveBy(MovementX(deltaTime), MovementY(deltaTime));

	if (GetPosition().y > SCREEN_HEIGHT + ENEMY_SIZE)
		RemoveEnemy();
}
