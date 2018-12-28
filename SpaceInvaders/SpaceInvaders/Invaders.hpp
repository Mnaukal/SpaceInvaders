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
#include <vector>
#include <iostream>

class Invaders : public Game
{
private:
	bool paused = false;
	// game objects
	Player player;
	std::vector<Rocket> rockets;
	std::vector<Rocket> enemyRockets;
	std::vector<Explosion> explosions;
	std::vector<std::unique_ptr<Enemy>> enemies;
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
	void UpdatePlayer(sf::Time deltaTime);
	void UpdateRockets(sf::Time deltaTime);
	void UpdateExplosions(sf::Time deltaTime);
	void PlayerShoot();
	void UpdateEnemies(sf::Time deltaTime);
	void EnemyShoot(sf::Vector2f position);
	void UpdateRocketsCollisions();
	void GenerateEnemy();
};

#endif
