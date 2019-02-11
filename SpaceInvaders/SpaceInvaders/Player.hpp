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
	sf::CircleShape shape;
	float shootTime;
public:
	float Speed = PLAYER_SPEED;
	float energy = 1.f;
	int Score = 0;
	Player();
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime) override;
	virtual sf::Rect<float> BoundingBox() override;
};
#endif


