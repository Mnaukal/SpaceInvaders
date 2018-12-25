#include "Rocket.hpp"

Rocket::Rocket() : shape(sf::Vector2f(10.f, 30.f)) {
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
};

void Rocket::Draw(sf::RenderWindow & window)
{
	shape.setPosition(position);
	window.draw(shape);
}