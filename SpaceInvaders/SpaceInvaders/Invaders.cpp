#include "Invaders.hpp"

Invaders::Invaders(const std::string & filename) 
	: timer(sf::Time::Zero), pausedOverlay(font), gameOverOverlay(font), gameOver_time(sf::Time::Zero)
{
	InitRandom();
	if (!LoadConfig(filename)) load_menu = true;
	if (!LoadTextures()) load_menu = true;

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

bool Invaders::LoadTextures()
{
	if (!font.loadFromFile(FONT_PATH))
	{
		error_message = "error loading font";
		return false;
	}
	if (!heart.loadFromFile(SPRITES_PATH + "heart.png"))
	{
		error_message = "error loading texture - heart";
		return false;
	}
	if (!heart_empty.loadFromFile(SPRITES_PATH + "heart_empty.png"))
	{
		error_message = "error loading texture - heart_empty";
		return false;
	}
	if (!player.loadFromFile(SPRITES_PATH + "player.png"))
	{
		error_message = "error loading texture - player";
		return false;
	}
	if (!simple_enemy.loadFromFile(SPRITES_PATH + "simple_enemy.png"))
	{
		error_message = "error loading texture - simple_enemy";
		return false;
	}
	if (!moving_enemy.loadFromFile(SPRITES_PATH + "moving_enemy.png"))
	{
		error_message = "error loading texture - moving_enemy";
		return false;
	}
	if (!shooting_enemy.loadFromFile(SPRITES_PATH + "shooting_enemy.png"))
	{
		error_message = "error loading texture - shooting_enemy";
		return false;
	}
	heart.setSmooth(false);
	heart_empty.setSmooth(false);
	return true;
}

bool Invaders::LoadConfig(const std::string & filename)
{
	std::ifstream input(CONFIG_PATH + filename);
	if(!input)
	{
		error_message =  "error opening config file - " + filename;
		return false;
	}

	unsigned line_num = 0;
	while (true)
	{
		line_num++;
		std::string name, value;
		std::getline(input, name, ':');
		std::getline(input, value, '\n');

		if (!input)
		{
			error_message = "error in config file - " + filename + ":\nno enemy waves declared";
			return false;
		}

		if (name == "WAVES")
			break;

		try {
			if (name == "LIVES") {
				PLAYER_LIVES = std::stoi(value);
				SCORE_TEXT_X = PLAYER_LIVES * 44 + 20;
			}
			else if (name == "SPEED") {
				PLAYER_SPEED = std::stof(value);
			}
			else if (name == "ENERGY_RESTORE") {
				PLAYER_ENERGY_RESTORE_RATE = std::stof(value);
			}
		}
		catch (const std::invalid_argument&) {
			error_message = "error in config file " + filename + " on line " + std::to_string(line_num) + ":\ninvalid number";
			return false;
		}
		catch (const std::out_of_range&) {
			error_message = "error in config file " + filename + " on line " + std::to_string(line_num) + ":\ninvalid number";
			return false;
		}
	}

	// waves
	while (true)
	{
		line_num++;
		std::string str;
		std::getline(input, str);

		if (!input)
			break;

		std::stringstream s(str);

		int count;
		std::string type;
		float min_time, max_time;

		s >> count;
		s >> type;
		s >> min_time;
		s >> max_time;

		if (!s)
		{
			error_message = "error in config file " + filename + " on line " + std::to_string(line_num) + ":\ninvalid wave declaration";
			return false;
		}

		EnemyWave w;
		w.count = count;
		w.min_time = min_time;
		w.max_time = max_time;
		w.spawn_simple = type.find("S") != std::string::npos;
		w.spawn_moving = type.find("M") != std::string::npos;
		w.spawn_shooting = type.find("H") != std::string::npos;

		enemy_waves.push_back(w);
	}
	return true;
}

bool Invaders::IsGameOver()
{
	if (load_menu)
		return true;

	return GameObjectManager::getInstance().player->lives <= 0;
}

void Invaders::Update(sf::Time deltaTime)
{
	if (paused)
		return;
	if (IsGameOver())
	{
		gameOver_time += deltaTime;
		return;
	}

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
	std::unique_ptr<Enemy> e = std::make_unique<MovingEnemy>(moving_enemy, (float)pos_x);
	e->SetPosition(sf::Vector2f((float)pos_x, 0.f));
	std::cout << "Generated MovingEnemy on x=" << pos_x << std::endl;
	GameObjectManager::getInstance().AddGameObject(std::move(e));
}

void Invaders::GenerateShootingEnemy()
{
	int pos_x = RandomNumber((int)shooting_enemy.getSize().x / 2, SCREEN_WIDTH + 1 - (int)shooting_enemy.getSize().x / 2);
	std::unique_ptr<Enemy> e = std::make_unique<ShootingEnemy>(shooting_enemy, (float)pos_x);
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
		if (event.key.code == sf::Keyboard::Escape && paused)
		{
			load_menu = true;
			return true;
		}
		if ((event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape) && IsGameOver() && gameOver_time.asSeconds() >= GAME_OVER_MIN_TIME)
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
	// do nothing
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

	if(error_message == "")
		return std::make_unique<TitleScreen>();
	else
		return std::make_unique<TitleScreen>(error_message);
}


