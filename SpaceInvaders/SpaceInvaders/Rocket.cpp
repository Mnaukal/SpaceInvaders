#include "Rocket.hpp"

Rocket::Rocket() : SIZE_X(10.f), SIZE_Y(45.f), shape(sf::Vector2f(10.f, 45.f)) {
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
	return sf::Rect<float>(position.x - SIZE_X / 2, position.y - SIZE_Y / 2, SIZE_X, SIZE_Y);
}

Explosion::Explosion(sf::Vector2f pos) : shape(sf::Vector2f(60.f, 60.f)), Animated(0.5f)
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
	scale = progress;
	shape.setFillColor(sf::Color(255, 255, 0, 255 * (1 - progress)));
	shape.setScale(sf::Vector2f(scale, scale));
}
