/*
	Game.hpp - general Game and GameObject definitions
*/

#ifndef game_hpp_
#define game_hpp_

#include <SFML/Graphics.hpp>

class Game
{
public:
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Draw(sf::RenderWindow & window) const = 0;
	// return true if event was handled, false if not
	virtual bool HandleEvent(const sf::Event & event) = 0; 
};

class GameObject 
{
public:
	virtual void Draw(sf::RenderWindow & window) const = 0;
	virtual void Update(sf::Time deltaTime) = 0;
};
#endif

