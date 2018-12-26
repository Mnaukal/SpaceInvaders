#include "Player.hpp"

Player::Player() : SIZE(80.f), shape(80.f, 3) {
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
};

void Player::Draw(sf::RenderWindow & window)
{
	shape.setPosition(position);
	window.draw(shape);
}

sf::Rect<float> Player::BoundingBox()
{
	return sf::Rect<float>(position.x - SIZE / 2, position.y - SIZE / 2, SIZE, SIZE); // TODO
}
