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
public :
	SimpleEnemy(const sf::Texture & texture) : Enemy(texture) {}
	// Inherited via Enemy
	virtual void Update(sf::Time deltaTime) override;
	virtual int EnemyScore() override { return KILL_SCORE_SIMPLE; }
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
	MovingEnemy(const sf::Texture & texture, float pos_x) : Enemy(texture), OriginalPosition(pos_x) {
		MovementDirection = RandomNumber(0, 2) == 1 ? Direction::Left : Direction::Right;
		HorizontalSpeed = RandomNumber(MOVING_ENEMY_MIN_HORIZONTAL_SPEED, MOVING_ENEMY_MAX_HORIZONTAL_SPEED);
		HorizontalRange = RandomNumber(MOVING_ENEMY_MIN_HORIZONTAL_RANGE, MOVING_ENEMY_MAX_HORIZONTAL_RANGE);
	};
	// Inherited via GameObject
	virtual void Update(sf::Time deltaTime) override;
	// Inherited via Enemy
	virtual int EnemyScore() override { return KILL_SCORE_MOVING; }
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
	ShootingEnemy(const sf::Texture & texture, float pos_x) : MovingEnemy(texture, pos_x) {
		HorizontalSpeed = RandomNumber(0, SHOOTING_ENEMY_MAX_HORIZONTAL_SPEED);
		HorizontalRange = RandomNumber(SHOOTING_ENEMY_MIN_HORIZONTAL_RANGE, SHOOTING_ENEMY_MAX_HORIZONTAL_RANGE);
		SetPosition(sf::Vector2f(pos_x, (float)RandomNumber(SHOOTING_ENEMY_MIN_Y_POSITION, SHOOTING_ENEMY_MAX_Y_POSITION)));
		RocketTimer = GetRocketTime();
	};
	// Inherited via GameObject
	virtual void Update(sf::Time deltaTime) override;
	// Inherited via Enemy
	virtual int EnemyScore() override { return KILL_SCORE_SHOOTING; }
protected:
	// Inherited via MovingEnemy
	virtual float MovementY(sf::Time deltaTime) override { return 0.0f; };
protected:
	// new methods
	float GetRocketTime() { return RandomNumber(SHOOTING_ENEMY_MIN_ROCKET_TIME, SHOOTING_ENEMY_MAX_ROCKET_TIME); };
};

#endif
