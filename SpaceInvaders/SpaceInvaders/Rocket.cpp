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

sf::Rect<float> Rocket::BoundingBox()
{
	return sf::Rect<float>(position.x - ROCKET_SIZE_X / 2, position.y - ROCKET_SIZE_Y / 2, ROCKET_SIZE_X, ROCKET_SIZE_Y);
}

Explosion::Explosion(sf::Vector2f pos) : shape(sf::Vector2f(EXPLOSION_SIZE, EXPLOSION_SIZE)), Animated(EXPLOSION_ANIMATION_DURATION)
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

sf::Rect<float> Explosion::BoundingBox()
{
	return sf::Rect<float>(position.x, position.y, 0, 0);
}

void Explosion::DoAnimation(float progress)
{
	scale = progress * EXPLOSION_ANIMATION_SCALING_SPEED;
	shape.setFillColor(sf::Color(255, 255, 0, 255 * (1 - progress)));
	shape.setScale(sf::Vector2f(scale, scale));
}
