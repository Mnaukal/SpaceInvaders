#include "Invaders.hpp"

Invaders::Invaders(const std::string & filename) 
	: timer(sf::Time::Zero), pausedOverlay(font), gameOverOverlay(font) 
{
	InitRandom();
	LoadConfig(filename);
	LoadTextures();

	GameObjectManager::getInstance().ClearAll();

	std::unique_ptr<Player> p = std::make_unique<Player>(player);
	p->SetPosition(sf::Vector2f(PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y)); 
	GameObjectManager::getInstance().player = &*p;
	GameObjectManager::getInstance().gameObjects.push_back(std::move(p));

	std::unique_ptr<EnergyBar> eb = std::make_unique<EnergyBar>(sf::Rect<int>(ENERGY_BAR_X, ENERGY_BAR_Y, ENERGY_BAR_WIDTH, ENERGY_BAR_HEIGHT));
	GameObjectManager::getInstance().AddUIObject(std::move(eb));
	std::unique_ptr<ScoreText> st = std::make_unique<ScoreText>(sf::Rect<int>(SCORE_TEXT_X, SCORE_TEXT_Y, SCORE_TEXT_WIDTH, SCORE_TEXT_HEIGHT), font);
	GameObjectManager::getInstance().AddUIObject(std::move(st));
	std::unique_ptr<LivesDisplay> ld = std::make_unique<LivesDisplay>(heart, heart_empty);
	GameObjectManager::getInstance().AddUIObject(std::move(ld));
}

void Invaders::LoadTextures()
{
	if (!font.loadFromFile(FONT_PATH))
	{
		std::cout << "Error loading font" << std::endl;
	}
	if (!heart.loadFromFile(SPRITES_PATH + "heart.png"))
	{
		std::cout << "Error loading texture - heart" << std::endl;
	}
	if (!heart_empty.loadFromFile(SPRITES_PATH + "heart_empty.png"))
	{
		std::cout << "Error loading texture - heart_empty" << std::endl;
	}
	if (!player.loadFromFile(SPRITES_PATH + "player.png"))
	{
		std::cout << "Error loading texture - player" << std::endl;
	}
	if (!simple_enemy.loadFromFile(SPRITES_PATH + "simple_enemy.png"))
	{
		std::cout << "Error loading texture - simple_enemy" << std::endl;
	}
	if (!moving_enemy.loadFromFile(SPRITES_PATH + "moving_enemy.png"))
	{
		std::cout << "Error loading texture - moving_enemy" << std::endl;
	}
	if (!shooting_enemy.loadFromFile(SPRITES_PATH + "shooting_enemy.png"))
	{
		std::cout << "Error loading texture - shooting_enemy" << std::endl;
	}
	heart.setSmooth(false);
	heart_empty.setSmooth(false);
}

void Invaders::LoadConfig(const std::string & filename)
{
	// TODO handle wrong input file

	std::ifstream input(CONFIG_PATH + filename);
	if(!input)
	{
		std::cout << "Error loading config - " << filename << std::endl;
		return;
	}
	int x;
	float y;
	// LIVES
	input >> x;
	PLAYER_LIVES = x;
	SCORE_TEXT_X = PLAYER_LIVES * 44 + 20;
	// SPEED
	input >> y;
	PLAYER_SPEED = y;
	// ENERGY_RESORE
	input >> y;
	PLAYER_ENERGY_RESTORE_RATE = y;

	// waves
	std::string s;
	input >> s;
	if (!input || s != "WAVES:")
	{
		std::cout << "Error loading enemy waves - " << filename << std::endl;
		return;
	}
	while (true)
	{
		int count;
		std::string type;
		float min_time, max_time;

		input >> count;
		input >> type;
		input >> min_time;
		input >> max_time;

		if (!input)
			break;

		EnemyWave w;
		w.count = count;
		w.min_time = min_time;
		w.max_time = max_time;
		w.spawn_simple = type.find("S") != std::string::npos;
		w.spawn_moving = type.find("M") != std::string::npos;
		w.spawn_shooting = type.find("H") != std::string::npos;

		enemy_waves.push_back(w);
	}
}

bool Invaders::IsGameOver()
{
	return GameObjectManager::getInstance().player->lives <= 0;
}

void Invaders::Update(sf::Time deltaTime)
{
	if (paused)
		return;
	if (IsGameOver())
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
		timer = sf::seconds(enemy_waves[current_wave].GetRandomSpawnTime());
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
	switch (enemy_waves[current_wave].GetRandomSpawnType())
	{
	case EnemyWave::Type::Simple:
		GenerateSimpleEnemy();
		break;
	case EnemyWave::Type::Moving:
		GenerateMovingEnemy();
		break;
	case EnemyWave::Type::Shooting:
		GenerateShootingEnemy();
		break;
	}

	if (enemy_waves[current_wave].count > 1)
		enemy_waves[current_wave].count--;
	else
		if (current_wave < enemy_waves.size() - 1)
			current_wave++;
}

void Invaders::GenerateSimpleEnemy()
{
	int pos_x = RandomNumber((int)simple_enemy.getSize().x / 2, SCREEN_WIDTH + 1 - (int)simple_enemy.getSize().x / 2);
	std::unique_ptr<Enemy> e = std::make_unique<SimpleEnemy>(simple_enemy);
	e->SetPosition(sf::Vector2f((float)pos_x, 0.f));
	std::cout << "Generated SimpleEnemy on x=" << pos_x << std::endl;
	GameObjectManager::getInstance().AddGameObject(std::move(e));
}

void Invaders::GenerateMovingEnemy()
{
	int pos_x = RandomNumber((int)moving_enemy.getSize().x / 2, SCREEN_WIDTH + 1 - (int)moving_enemy.getSize().x / 2);
	std::unique_ptr<Enemy> e = std::make_unique<MovingEnemy>(moving_enemy, pos_x);
	e->SetPosition(sf::Vector2f((float)pos_x, 0.f));
	std::cout << "Generated MovingEnemy on x=" << pos_x << std::endl;
	GameObjectManager::getInstance().AddGameObject(std::move(e));
}

void Invaders::GenerateShootingEnemy()
{
	int pos_x = RandomNumber((int)shooting_enemy.getSize().x / 2, SCREEN_WIDTH + 1 - (int)shooting_enemy.getSize().x / 2);
	std::unique_ptr<Enemy> e = std::make_unique<ShootingEnemy>(shooting_enemy, pos_x);
	std::cout << "Generated ShootingEnemy on x=" << pos_x << std::endl;
	GameObjectManager::getInstance().AddGameObject(std::move(e));
}

bool Invaders::HandleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::P)
		{
			paused = !paused;
			return true;
		}
		if (IsGameOver())
		{
			load_menu = true;
			return true;
		}
	}

	return false;
}

void Invaders::Draw(sf::RenderWindow & window)
{
	for (auto it = GameObjectManager::getInstance().gameObjects.rbegin(); it != GameObjectManager::getInstance().gameObjects.rend(); ++it)
	{
		(**it).Draw(window);
	}
	for (auto && go : GameObjectManager::getInstance().UIobjects)
	{
		go->Draw(window);
	}

	if (IsGameOver())
	{
		gameOverOverlay.Draw(window);
		return;
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

std::unique_ptr<Game> Invaders::LoadLevel()
{
	if (!load_menu)
		return nullptr;

	return std::make_unique<TitleScreen>();
}


