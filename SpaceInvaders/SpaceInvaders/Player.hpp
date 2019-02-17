/*
Player.hpp - code for user controlled player
*/

#ifndef player_hpp_
#define player_hpp_

#include "Game.hpp"
#include "Rocket.hpp"
#include "InvadersConstants.hpp"
#include "GameObjectManager.hpp"

class Player : public GameObject
{
private:
	sf::Sprite sprite;
	int width, height;
	float shootTime;
public:
	float Speed;
	float energy = 1.f;
	int Score = 0;
	int lives; 
	Player(const sf::Texture & texture);
	void HitPlayer(); // subtract life
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime) override;
	virtual sf::Rect<float> BoundingBox() override;
};

class HitEffect : public GameObject, public Animated {
private:
	sf::RectangleShape shape;
public:
	HitEffect();
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime);
	virtual sf::Rect<float> BoundingBox() { return sf::Rect<float>(); };
	// Inherited via Animated
	virtual void DoAnimation(float progress) override;
};
#endif


