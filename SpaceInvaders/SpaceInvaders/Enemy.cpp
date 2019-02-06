#include "Enemy.hpp"

void Enemy::RemoveEnemy()
{
	GameObjectManager::getInstance().RemoveGameObject(this);
}

Enemy::Enemy() : Size(ENEMY_SIZE), shape(sf::Vector2f(ENEMY_SIZE, ENEMY_SIZE))
{
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
}

void Enemy::Draw(sf::RenderWindow & window)
{
	shape.setPosition(position);
	window.draw(shape);
}

sf::Rect<float> Enemy::BoundingBox()
{
	return sf::Rect<float>(position.x - Size/2, position.y - Size/2, Size, Size);
}

