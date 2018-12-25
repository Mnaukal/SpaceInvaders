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
public:
	float Speed = 300;
	Player();
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
};
#endif


