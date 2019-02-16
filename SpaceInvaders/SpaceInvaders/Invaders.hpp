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
#include "EnemyWave.hpp"
#include <vector>
#include <iostream>
#include <fstream>

class Invaders : public Game
{
private:
	bool paused = false;
	sf::Time timer;
	sf::Font font;
	sf::Texture heart, heart_empty, player, simple_enemy, moving_enemy, shooting_enemy;
	PausedText pausedOverlay;
	std::vector<EnemyWave> enemy_waves;
	int current_wave = 0;
public:
	Invaders(const std::string & filename); // filename = config file
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
	void GenerateSimpleEnemy();
	void GenerateMovingEnemy();
	void GenerateShootingEnemy();
	void LoadTextures();
	void LoadConfig(const std::string & filename);
};

#endif
