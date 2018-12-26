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
