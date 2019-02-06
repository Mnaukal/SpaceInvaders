/*
Enemies.hpp - different types of enemies
*/

#ifndef enemies_hpp_
#define enemies_hpp_

#include "Enemy.hpp"
#include "Common.hpp"
#include "Rocket.hpp"
#include "GameObjectManager.hpp"
#include <algorithm>

class SimpleEnemy : public Enemy
{
	// Inherited via Enemy
	virtual void Update(sf::Time deltaTime) override;
};

class MovingEnemy : public Enemy
{
protected:
	enum Direction : bool { Left, Right };
	int HorizontalSpeed;
	int HorizontalRange;
	float OriginalPosition;
	Direction MovementDirection;
public:
	MovingEnemy(float pos_x) : Enemy(), OriginalPosition(pos_x) { 
		MovementDirection = RandomNumber(0, 2) == 1 ? Direction::Left : Direction::Right;
		HorizontalSpeed = RandomNumber(0, MOVING_ENEMY_MAX_HORIZONTAL_SPEED);
		HorizontalRange = RandomNumber(MOVING_ENEMY_MIN_HORIZONTAL_RANGE, MOVING_ENEMY_MAX_HORIZONTAL_RANGE);
	};
	// Inherited via GameObject
	virtual void Update(sf::Time deltaTime) override;
protected:
	// new methods
	virtual float MovementX(sf::Time deltaTime);
	virtual float MovementY(sf::Time deltaTime);
};

class ShootingEnemy : public MovingEnemy 
{
protected:
	float RocketTimer = 0;
public:
	ShootingEnemy(float pos_x) : MovingEnemy(pos_x) {
		HorizontalSpeed = RandomNumber(0, SHOOTING_ENEMY_MAX_HORIZONTAL_SPEED);
		HorizontalRange = RandomNumber(SHOOTING_ENEMY_MIN_HORIZONTAL_RANGE, SHOOTING_ENEMY_MAX_HORIZONTAL_RANGE);
		SetPosition(sf::Vector2f(pos_x, (float)RandomNumber(SHOOTING_ENEMY_MIN_Y_POSITION, SHOOTING_ENEMY_MAX_Y_POSITION)));
		RocketTimer = GetRocketTime();
	};
	// Inherited via GameObject
	virtual void Update(sf::Time deltaTime) override;
protected:
	// Inherited via MovingEnemy
	virtual float MovementY(sf::Time deltaTime) override { return 0; };
protected:
	// new methods
	float GetRocketTime() { return RandomNumber(SHOOTING_ENEMY_MIN_ROCKET_TIME, SHOOTING_ENEMY_MAX_ROCKET_TIME); };
};

#endif
