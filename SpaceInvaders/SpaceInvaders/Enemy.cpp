#include "Enemy.hpp"

void Enemy::RemoveEnemy()
{
	GameObjectManager::getInstance().RemoveGameObject(this);

}

void Enemy::HitPlayerOnce()
{
	if (!did_hit)
	{
		GameObjectManager::getInstance().player->HitPlayer();
		did_hit = true;
	}
}

Enemy::Enemy(const sf::Texture & texture)
{
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	width = texture.getSize().x;
	height = texture.getSize().y;
}

void Enemy::Draw(sf::RenderWindow & window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

sf::Rect<float> Enemy::BoundingBox()
{
	return sf::Rect<float>((float)(position.x - width/2), (float)(position.y - height/2), (float)width, (float)height);
}

void Enemy::Collide(GameObject * other, sf::FloatRect intersection)
{
	Player* p = dynamic_cast<Player*>(other);
	if (p != nullptr)
	{
		// create explosion
		std::unique_ptr<Explosion> expl = std::make_unique<Explosion>(Center(intersection), SMALL_EXPLOSION_SIZE);
		GameObjectManager::getInstance().AddUIObject(std::move(expl));
		// hit player
		HitPlayerOnce();
		// remove enemy
		RemoveEnemy();
	}
}

