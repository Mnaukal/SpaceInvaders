#include "Rocket.hpp"

Rocket::Rocket() : shape(sf::Vector2f(ROCKET_SIZE_X, ROCKET_SIZE_Y)) {
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
};

void Rocket::Draw(sf::RenderWindow & window)
{
	shape.setPosition(position);
	window.draw(shape);
}

void Rocket::Update(sf::Time deltaTime)
{
	MoveBy(0, -deltaTime.asSeconds() * Speed);

	// remove rocket
	if (GetPosition().y < 0 - ROCKET_SIZE_Y / 2 || GetPosition().y > SCREEN_HEIGHT + ROCKET_SIZE_Y / 2)
		GameObjectManager::getInstance().RemoveGameObject(this);
}

void Rocket::Collide(GameObject * other, sf::FloatRect intersection)
{
	Enemy* e = dynamic_cast<Enemy*>(other);
	if (e != nullptr)
	{
		// create explosion
		std::unique_ptr<Explosion> expl = std::make_unique<Explosion>(Center(intersection));
		GameObjectManager::getInstance().AddUIObject(std::move(expl));
		// add score
		GameObjectManager::getInstance().player->Score += e->EnemyScore();
		// remove enemy and rocket
		e->RemoveEnemy();
		GameObjectManager::getInstance().RemoveGameObject(this);
	}
}

sf::Rect<float> Rocket::BoundingBox()
{
	return sf::Rect<float>(position.x - ROCKET_SIZE_X / 2, position.y - ROCKET_SIZE_Y / 2, ROCKET_SIZE_X, ROCKET_SIZE_Y);
}

Explosion::Explosion(sf::Vector2f pos) : Explosion(pos, EXPLOSION_SIZE) { }

Explosion::Explosion(sf::Vector2f pos, float size)
	: shape(sf::Vector2f(size, size)), Animated(EXPLOSION_ANIMATION_DURATION)
{
	position = pos;
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	shape.setFillColor(sf::Color(255, 255, 0, 255));
	shape.setScale(sf::Vector2f(0, 0));
	shape.setPosition(position);
}

void Explosion::Draw(sf::RenderWindow & window)
{
	window.draw(shape);
}

void Explosion::Update(sf::Time deltaTime)
{
	if(Animate(deltaTime))
		GameObjectManager::getInstance().RemoveUIObject(this);
}

sf::Rect<float> Explosion::BoundingBox()
{
	return sf::Rect<float>(position.x, position.y, 0, 0);
}

void Explosion::DoAnimation(float progress)
{
	scale = progress * EXPLOSION_ANIMATION_SCALING_SPEED;
	shape.setFillColor(sf::Color(255, 255, 0, (sf::Uint8)(255 * (1 - progress))));
	shape.setScale(sf::Vector2f(scale, scale));
}

void EnemyRocket::Collide(GameObject * other, sf::FloatRect intersection)
{
	Player* p = dynamic_cast<Player*>(other);
	if (p != nullptr)
	{
		// create explosion
		std::unique_ptr<Explosion> expl = std::make_unique<Explosion>(Center(intersection), SMALL_EXPLOSION_SIZE);
		GameObjectManager::getInstance().AddUIObject(std::move(expl));
		// hit player
		GameObjectManager::getInstance().player->HitPlayer();
		// remove rocket
		GameObjectManager::getInstance().RemoveGameObject(this);
	}
}
