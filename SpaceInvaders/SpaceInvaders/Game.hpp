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
	virtual void Draw(sf::RenderWindow & window) = 0;
	// return true if event was handled, false if not
	virtual bool HandleEvent(const sf::Event & event) = 0; 
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void SaveAndExit() = 0;
	virtual sf::View Resize(unsigned width, unsigned height) = 0;
};

class GameObject 
{
protected:
	sf::Vector2f position;
public:
	virtual void Draw(sf::RenderWindow & window) = 0;
	//virtual void Update(sf::Time deltaTime) = 0;
	void MoveBy(float x, float y) { position.x += x; position.y += y; };
	sf::Vector2f GetPosition() const { return position; };
	void SetPosition(sf::Vector2f newPosition) { position = newPosition; };
};
#endif

