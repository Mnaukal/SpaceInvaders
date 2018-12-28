#include "Invaders.hpp"

Invaders::Invaders() : player(), timer(sf::Time::Zero) {
	InitRandom();
	player.SetPosition(sf::Vector2f(PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y)); 
}

void Invaders::Update(sf::Time deltaTime)
{
	if (paused)
		return;

	UpdatePlayer(deltaTime);
	UpdateRockets(deltaTime);
	UpdateExplosions(deltaTime);
	UpdateEnemies(deltaTime);
	UpdateRocketsCollisions();

	timer -= deltaTime;
	if (timer <= sf::Time::Zero)
	{
		GenerateEnemy();
		timer = sf::seconds(RandomNumber(0, 3));
	}
}

void Invaders::UpdatePlayer(sf::Time deltaTime)
{
	// move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		float deltaX = deltaTime.asSeconds() * player.Speed;
		if (player.GetPosition().x + deltaX < SCREEN_WIDTH)
			player.MoveBy(deltaX, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		float deltaX = deltaTime.asSeconds() * player.Speed;
		if (player.GetPosition().x - deltaX > 0)
			player.MoveBy(-deltaX, 0);
	}

	// shooting done as event
}

void Invaders::UpdateRockets(sf::Time deltaTime)
{
	for (auto r = rockets.begin(); r != rockets.end();)
	{
		r->MoveBy(0, -deltaTime.asSeconds() * r->Speed);

		// remove rocket
		if (r->GetPosition().y < 0 - ROCKET_SIZE_Y / 2)
			r = rockets.erase(r); // TODO possible to swap with last and delete faster
		else
			++r;
	}

	for (auto r = enemyRockets.begin(); r != enemyRockets.end();)
	{
		r->MoveBy(0, -deltaTime.asSeconds() * r->Speed);

		// remove rocket
		if (r->GetPosition().y < 0 - ROCKET_SIZE_Y / 2)
			r = enemyRockets.erase(r); // TODO possible to swap with last and delete faster
		else
			++r;
	}
}

void Invaders::UpdateExplosions(sf::Time deltaTime)
{
	for (auto e = explosions.begin(); e != explosions.end();)
	{
		if (e->Animate(deltaTime))
			e = explosions.erase(e); // TODO possible to swap with last and delete faster
		else
			++e;
	}
}

void Invaders::PlayerShoot()
{
	Rocket r;
	r.SetPosition(player.GetPosition());
	rockets.push_back(r);
}

void Invaders::UpdateEnemies(sf::Time deltaTime)
{
	for (auto e = enemies.begin(); e != enemies.end();)
	{
		(*e)->UpdateEnemy(deltaTime);
		
		Enemy* pe = &**e;
		ShootingEnemy* se = dynamic_cast<ShootingEnemy*>(pe);
		if (se != nullptr)
			if (se->ShootRocket())
				EnemyShoot(se->GetPosition());

		// remove enemy
		if ((*e)->GetPosition().y > SCREEN_HEIGHT + ENEMY_SIZE) // TODO number (enemy size may vary in future)
			e = enemies.erase(e); // TODO possible to swap with last and delete faster
		else
			++e;
	}
}

void Invaders::EnemyShoot(sf::Vector2f position)
{
	Rocket r(-ROCKET_SPEED);
	r.SetPosition(position);
	enemyRockets.push_back(r);
}

void Invaders::UpdateRocketsCollisions()
{
	for (auto r = rockets.begin(); r != rockets.end();)
	{
		for (auto e = enemies.begin(); e != enemies.end();)
		{
			sf::Rect<float> intersection;
			if ((*e)->BoundingBox().intersects(r->BoundingBox(), intersection)) // rocket hits enemy
			{
				Explosion expl(Center(intersection));
				explosions.push_back(expl);
				r = rockets.erase(r); // TODO possible to swap with last and delete faster
				e = enemies.erase(e);
				break;
			}
			else
				++e;
		}

		if(r != rockets.end())
			++r;
	}

	for (auto r = enemyRockets.begin(); r != enemyRockets.end();)
	{
		sf::Rect<float> intersection;
		if (player.BoundingBox().intersects(r->BoundingBox(), intersection)) // rocket hits enemy
		{
			Explosion expl(Center(intersection));
			explosions.push_back(expl);
			r = enemyRockets.erase(r); // TODO possible to swap with last and delete faster
			break;
		}
		else
			++r;
	}
}

void Invaders::GenerateEnemy()
{
	int pos_x = RandomNumber(ENEMY_SIZE / 2, SCREEN_WIDTH + 1);
	std::unique_ptr<Enemy> e = std::make_unique<ShootingEnemy>(pos_x);
	//e->SetPosition(sf::Vector2f(pos_x, 0)); // TODO number (enemy size may vary in future)
	std::cout << "Generated ShootingEnemy on x=" << pos_x << std::endl;
	enemies.push_back(std::move(e));
}

bool Invaders::HandleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			PlayerShoot();
		}
	}

	return false;
}

void Invaders::Draw(sf::RenderWindow & window)
{
	for (auto && r : rockets)
		r.Draw(window);
	for (auto && r : enemyRockets)
		r.Draw(window);
	for (auto && e : enemies)
		e->Draw(window);
	player.Draw(window);
	for (auto && e : explosions)
		e.Draw(window);
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
