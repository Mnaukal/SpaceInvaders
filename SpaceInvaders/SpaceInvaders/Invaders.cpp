#include "Invaders.hpp"

Invaders::Invaders() : timer(sf::Time::Zero), pausedOverlay(font) {
	InitRandom();

	if (!font.loadFromFile(FONT_PATH))
	{
		std::cout << "Error loading font" << std::endl;
	}

	std::unique_ptr<Player> p = std::make_unique<Player>();
	p->SetPosition(sf::Vector2f(PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y)); 
	GameObjectManager::getInstance().player = &*p;
	GameObjectManager::getInstance().gameObjects.push_back(std::move(p));

	std::unique_ptr<EnergyBar> eb = std::make_unique<EnergyBar>(sf::Rect<int>(ENERGY_BAR_X, ENERGY_BAR_Y, ENERGY_BAR_WIDTH, ENERGY_BAR_HEIGHT));
	GameObjectManager::getInstance().AddUIObject(std::move(eb));
	std::unique_ptr<ScoreText> st = std::make_unique<ScoreText>(sf::Rect<int>(SCORE_TEXT_X, SCORE_TEXT_Y, SCORE_TEXT_WIDTH, SCORE_TEXT_HEIGHT), font);
	GameObjectManager::getInstance().AddUIObject(std::move(st));
}

void Invaders::Update(sf::Time deltaTime)
{
	if (paused)
		return;

	for (auto && go : GameObjectManager::getInstance().gameObjects)
	{
		go->Update(deltaTime);
	}
	for (auto && go : GameObjectManager::getInstance().UIobjects)
	{
		if(go != nullptr)
			go->Update(deltaTime);
	}

	UpdateCollisions();

	timer -= deltaTime;
	if (timer <= sf::Time::Zero)
	{
		GenerateEnemy();
		timer = sf::seconds(RandomNumber(0, 3));
	}

	GameObjectManager::getInstance().Update();
}

void Invaders::UpdateCollisions()
{
	for (size_t i = 0; i < GameObjectManager::getInstance().gameObjects.size(); i++)
	{
		for (size_t j = 0; j < GameObjectManager::getInstance().gameObjects.size(); j++)
		{
			if (i == j) continue;

			sf::Rect<float> intersection;
			if (GameObjectManager::getInstance().gameObjects[i]->BoundingBox().intersects(GameObjectManager::getInstance().gameObjects[j]->BoundingBox(), intersection)) // rocket hits enemy
			{
				GameObjectManager::getInstance().gameObjects[i]->Collide(&*GameObjectManager::getInstance().gameObjects[j], intersection);
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
	for (auto && go : GameObjectManager::getInstance().gameObjects)
	{
		go->Draw(window);
	}
	for (auto && go : GameObjectManager::getInstance().UIobjects)
	{
		go->Draw(window);
	}

	if (paused)
		pausedOverlay.Draw(window);
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


