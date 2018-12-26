#include "Enemy.hpp"

Enemy::Enemy() : SIZE(60.f), shape(sf::Vector2f(60.f, 60.f))
{
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
}

void Enemy::Draw(sf::RenderWindow & window)
{
	shape.setPosition(position);
	window.draw(shape);
}

sf::Rect<float> Enemy::BoundingBox()
{
	return sf::Rect<float>(position.x - SIZE/2, position.y - SIZE/2, SIZE, SIZE);
}
