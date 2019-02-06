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

void Player::Update(sf::Time deltaTime)
{
	// move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		float deltaX = deltaTime.asSeconds() * Speed;
		if (GetPosition().x + deltaX < SCREEN_WIDTH)
			MoveBy(deltaX, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		float deltaX = deltaTime.asSeconds() * Speed;
		if (GetPosition().x - deltaX > 0)
			MoveBy(-deltaX, 0);
	}

	// shooting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // TODO timing
	{
		std::unique_ptr<Rocket> r = std::make_unique<Rocket>(ROCKET_SPEED);
		r->SetPosition(GetPosition());
		GameObjectManager::getInstance().AddGameObject(std::move(r));
	}
}

sf::Rect<float> Player::BoundingBox()
{
	return sf::Rect<float>(position.x - PLAYER_SIZE / 2, position.y - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE);
}
