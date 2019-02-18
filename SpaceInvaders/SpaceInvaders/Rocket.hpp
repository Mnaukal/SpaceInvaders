/*
Rocket.hpp - code for rockets shot by player
*/

#ifndef rocket_hpp_
#define rocket_hpp_

#include "Game.hpp"
#include "InvadersConstants.hpp"
#include "GameObjectManager.hpp"
#include "Enemy.hpp"
#include "Common.hpp"

class Rocket : public GameObject
{
private:
	sf::RectangleShape shape;
public:
	float Speed = ROCKET_SPEED;
	Rocket();
	Rocket(float speed) : Rocket() { Speed = speed; };
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void Collide(GameObject* other, sf::FloatRect intersection) override;
	virtual sf::Rect<float> BoundingBox() override;
};

class EnemyRocket : public Rocket {
public:
	EnemyRocket(float speed) : Rocket(-speed) {};
	virtual void Collide(GameObject* other, sf::FloatRect intersection) override;
};

class Explosion : public GameObject, public Animated
{
private:
	sf::RectangleShape shape;
	float scale = 0;
public:
	Explosion(sf::Vector2f pos);
	Explosion(sf::Vector2f pos, float size);
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime) override;
	virtual sf::Rect<float> BoundingBox() override;
	// Inherited via Animated
	virtual void DoAnimation(float progress) override;
};
#endif


