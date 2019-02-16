#include "Enemy.hpp"

void Enemy::RemoveEnemy()
{
	GameObjectManager::getInstance().RemoveGameObject(this);

}

Enemy::Enemy(const sf::Texture & texture)
{
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
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
	return sf::Rect<float>(position.x - width/2, position.y - height/2, width, height);
}

