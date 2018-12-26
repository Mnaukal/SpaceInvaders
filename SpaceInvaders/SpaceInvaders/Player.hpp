/*
Player.hpp - code for user controlled player
*/

#ifndef player_hpp_
#define player_hpp_

#include "Game.hpp"

class Player : public GameObject
{
private:
	sf::CircleShape shape;
	float SIZE;
public:
	float Speed = 300;
	Player();
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual sf::Rect<float> BoundingBox() override;
};
#endif


