#include "Invaders.hpp"

Invaders::Invaders() : player(), Size(1280, 720), timer(sf::Time::Zero) {
	InitRandom();
	player.SetPosition(sf::Vector2f(Size.x / 2, Size.y - 23)); // TODO number
}

void Invaders::Update(sf::Time deltaTime)
{
	if (paused)
		return;

	UpdatePlayer(deltaTime);
	UpdateRockets(deltaTime);
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
		if (player.GetPosition().x + deltaX < Size.x)
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
		if (r->GetPosition().y < 0 - 30) // TODO number
			r = rockets.erase(r); // TODO possible to swap with last and delete faster
		else
			++r;
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
		(*e)->MoveBy(0, deltaTime.asSeconds() * (*e)->Speed);

		// remove rocket
		if ((*e)->GetPosition().y > Size.y) // TODO number
			e = enemies.erase(e); // TODO possible to swap with last and delete faster
		else
			++e;
	}
}

void Invaders::UpdateRocketsCollisions()
{
	for (auto r = rockets.begin(); r != rockets.end();)
	{
		for (auto e = enemies.begin(); e != enemies.end();)
		{
			if ((*e)->BoundingBox().intersects(r->BoundingBox())) // rocket hits enemy
			{
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
}

void Invaders::GenerateEnemy()
{
	std::unique_ptr<Enemy> e = std::make_unique<Enemy>();
	e->SetPosition(sf::Vector2f(RandomNumber(30, 1251), 0)); // TODO numbers
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
	for (auto && e : enemies)
		e->Draw(window);
	player.Draw(window);
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
