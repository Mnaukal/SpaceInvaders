#include "Player.hpp"

Player::Player(const sf::Texture & texture) : shootTime(0), Speed(PLAYER_SPEED) {
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y);
	width = texture.getSize().x;
	height = texture.getSize().y;
};

void Player::Draw(sf::RenderWindow & window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Player::Update(sf::Time deltaTime)
{
	// move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		float deltaX = deltaTime.asSeconds() * Speed;
		if (GetPosition().x + deltaX < SCREEN_WIDTH - width / 2)
			MoveBy(deltaX, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		float deltaX = deltaTime.asSeconds() * Speed;
		if (GetPosition().x - deltaX > 0 + width / 2)
			MoveBy(-deltaX, 0);
	}

	// shooting
	if (shootTime > 0)
		shootTime -= deltaTime.asSeconds();
	energy = std::min(energy + PLAYER_ENERGY_RESTORE_RATE * deltaTime.asSeconds(), 1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (shootTime <= 0 && energy > PLAYER_ENERGY_SHOOT)
		{
			std::unique_ptr<Rocket> r = std::make_unique<Rocket>(ROCKET_SPEED);
			r->SetPosition(GetPosition() - sf::Vector2f(0, height));
			GameObjectManager::getInstance().AddGameObject(std::move(r));
			shootTime = PLAYER_MIN_SHOOT_TIME;
			energy -= PLAYER_ENERGY_SHOOT;
		}
	}
}

sf::Rect<float> Player::BoundingBox()
{
	return sf::Rect<float>(position.x - width / 2, position.y - height, width, height);
}
