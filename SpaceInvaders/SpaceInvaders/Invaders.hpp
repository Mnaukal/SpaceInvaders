/*
Invaders.hpp - main game code
*/

#ifndef invaders_hpp_
#define invaders_hpp_

#include "Game.hpp"
#include "Player.hpp"
#include "Rocket.hpp"
#include <vector>

class Invaders : public Game
{
private:
	bool paused = false;
	const sf::Vector2i Size;
	// game objects
	Player player;
	std::vector<Rocket> rockets;
public:
	Invaders();
	// Inherited via Game
	virtual void Update(sf::Time deltaTime) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual bool HandleEvent(const sf::Event & event) override;
	virtual void Pause() override;
	virtual void Resume() override;
	virtual void SaveAndExit() override;
	virtual sf::View Resize(unsigned width, unsigned height) override;
private:
	void UpdatePlayer(sf::Time deltaTime);
	void UpdateRockets(sf::Time deltaTime);
	void PlayerShoot();
};

#endif
