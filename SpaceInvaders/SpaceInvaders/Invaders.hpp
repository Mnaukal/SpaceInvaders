/*
Invaders.hpp - main game code
*/

#ifndef invaders_hpp_
#define invaders_hpp_

//#include <SFML/Graphics.hpp>
#include "Game.hpp"

class Invaders : public Game
{
public:
	Invaders();
	// inherited from Game
	virtual void Update(sf::Time deltaTime) override;
	virtual void Draw(sf::RenderWindow & window) const override;
	virtual bool HandleEvent(const sf::Event & event) override;
};

#endif
