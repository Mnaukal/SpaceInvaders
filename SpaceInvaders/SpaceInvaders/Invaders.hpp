/*
Invaders.hpp - main game code
*/

#ifndef invaders_hpp_
#define invaders_hpp_

#include "Game.hpp"
#include "Player.hpp"
#include "Rocket.hpp"
#include "Enemy.hpp"
#include "Common.hpp"
#include "InvadersConstants.hpp"
#include "Enemies.hpp"
#include "GameObjectManager.hpp"
#include "UserInterface.hpp"
#include <vector>
#include <iostream>

class Invaders : public Game
{
private:
	bool paused = false;
	sf::Time timer;
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
	void UpdateCollisions();
	void GenerateEnemy();
};

#endif
