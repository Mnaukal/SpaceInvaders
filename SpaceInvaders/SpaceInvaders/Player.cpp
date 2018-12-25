#include "Player.hpp"

Player::Player() : shape(80.f, 3) {
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	position.y = 720 - 80; // TODO
};

void Player::Draw(sf::RenderWindow & window)
{
	shape.setPosition(position);
	window.draw(shape);
}