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
#include "TitleScreen.hpp"
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
	GameOverText gameOverOverlay;
	std::vector<EnemyWave> enemy_waves;
	unsigned current_wave = 0;
	bool load_menu = false; // se to true to return to main menu
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
	virtual bool WantLoadLevel() override { return load_menu; }
	virtual std::unique_ptr<Game> LoadLevel() override;
private:
	void UpdateCollisions();
	void GenerateEnemy();
	void GenerateSimpleEnemy();
	void GenerateMovingEnemy();
	void GenerateShootingEnemy();
	void LoadTextures();
	void LoadConfig(const std::string & filename);
	bool IsGameOver(); // true if game is over and should be stopped
};

#endif
