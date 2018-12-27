#include "Player.hpp"

Player::Player() : shape(PLAYER_SIZE, 3) {
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
};

void Player::Draw(sf::RenderWindow & window)
{
	shape.setPosition(position);
	window.draw(shape);
}

sf::Rect<float> Player::BoundingBox()
{
	return sf::Rect<float>(position.x - PLAYER_SIZE / 2, position.y - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE);
}
