/*
Rocket.hpp - code for rockets shot by player
*/

#ifndef rocket_hpp_
#define rocket_hpp_

#include "Game.hpp"

class Rocket : public GameObject
{
private:
	sf::RectangleShape shape;
	float SIZE_X, SIZE_Y;
public:
	float Speed = 500;
	Rocket();
	Rocket(float speed) : Rocket() { Speed = speed; };
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual sf::Rect<float> BoundingBox() override;
};

class Explosion : public GameObject, public Animated
{
private:
	sf::RectangleShape shape;
	float scale = 0;
public:
	Explosion(sf::Vector2f pos);
	float ScaleSpeed = 3.f;
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual sf::Rect<float> BoundingBox() override;
	// Inherited via Animated
	virtual void DoAnimation(float progress) override;
};
#endif


