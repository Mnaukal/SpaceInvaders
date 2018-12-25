#include "Invaders.hpp"

sf::CircleShape shape;

Invaders::Invaders()
{
	shape.setRadius(100.f);
	shape.setFillColor(sf::Color::Green);
}

void Invaders::Update(sf::Time deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		shape.setFillColor(sf::Color(shape.getFillColor().r - 1, shape.getFillColor().g, shape.getFillColor().b, shape.getFillColor().a));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		shape.setFillColor(sf::Color(shape.getFillColor().r + 1, shape.getFillColor().g, shape.getFillColor().b, shape.getFillColor().a));
}

void Invaders::Draw(sf::RenderWindow & window) const
{
	window.draw(shape);
}

bool Invaders::HandleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Key::Up)
			shape.setRadius(shape.getRadius() + 1);
		if (event.key.code == sf::Keyboard::Key::Down)
			shape.setRadius(shape.getRadius() - 1);
		return true;
	}
	if (event.type == sf::Event::MouseMoved) {
		shape.setPosition(event.mouseMove.x, event.mouseMove.y);
		return true;
	}

	return false;
}
