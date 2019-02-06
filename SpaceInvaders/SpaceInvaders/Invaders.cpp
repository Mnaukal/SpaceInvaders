#include "Invaders.hpp"

Invaders::Invaders() : timer(sf::Time::Zero) {
	InitRandom();

	std::unique_ptr<Player> p = std::make_unique<Player>();
	p->SetPosition(sf::Vector2f(PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y)); 
	gameObjects.push_back(std::move(p));
}

void Invaders::AddGameObjects()
{
	for (size_t i = 0; i < GameObjectManager::getInstance().AddedGameObjects.size(); i++)
	{
		gameObjects.push_back(std::move(GameObjectManager::getInstance().AddedGameObjects[i]));
	}
	GameObjectManager::getInstance().AddedGameObjects.clear();
}

void Invaders::RemoveGameObjects()
{
	for (auto r : GameObjectManager::getInstance().RemovedGameObjects)
	{
		auto go = std::find_if(gameObjects.begin(), gameObjects.end(), [r](const std::unique_ptr<GameObject>& p) {
			return p.get() == r;
		});
		if (go == gameObjects.end()) continue;

		go->swap(gameObjects.back());
		gameObjects.back().reset();
		gameObjects.pop_back();
	}
	GameObjectManager::getInstance().RemovedGameObjects.clear();
}

void Invaders::Update(sf::Time deltaTime)
{
	if (paused)
		return;

	for (auto && go : gameObjects)
	{
		go->Update(deltaTime);
	}

	UpdateCollisions();

	timer -= deltaTime;
	if (timer <= sf::Time::Zero)
	{
		GenerateEnemy();
		timer = sf::seconds(RandomNumber(0, 3));
	}

	RemoveGameObjects();
	AddGameObjects();
}

void Invaders::UpdateCollisions()
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		for (size_t j = 0; j < gameObjects.size(); j++)
		{
			if (i == j) continue;

			sf::Rect<float> intersection;
			if (gameObjects[i]->BoundingBox().intersects(gameObjects[j]->BoundingBox(), intersection)) // rocket hits enemy
			{
				gameObjects[i]->Collide(&*gameObjects[j], intersection);
			}
		}
	}
}

void Invaders::GenerateEnemy()
{
	int pos_x = RandomNumber((int)(ENEMY_SIZE / 2), SCREEN_WIDTH + 1);
	std::unique_ptr<Enemy> e = std::make_unique<ShootingEnemy>((float)pos_x);
	//e->SetPosition(sf::Vector2f(pos_x, 0)); // TODO number (enemy size may vary in future)
	std::cout << "Generated ShootingEnemy on x=" << pos_x << std::endl;
	GameObjectManager::getInstance().AddGameObject(std::move(e));
}

bool Invaders::HandleEvent(const sf::Event & event)
{
	return false;
}

void Invaders::Draw(sf::RenderWindow & window)
{
	for (auto && go : gameObjects)
	{
		go->Draw(window);
	}
}

void Invaders::Pause()
{
	paused = true;
}

void Invaders::Resume()
{
	paused = false;
}

void Invaders::SaveAndExit()
{
	// TODO
}

sf::View Invaders::Resize(unsigned width, unsigned height)
{
	// TODO
	return sf::View();
}


