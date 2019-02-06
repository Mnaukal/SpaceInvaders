#include "UserInterface.hpp"

EnergyBar::EnergyBar(sf::Rect<int> position) : background(sf::Vector2f(position.width, position.height)), progress(sf::Vector2f(position.width, position.height))
{
	background.setPosition(position.left, position.top);
	background.setFillColor(sf::Color::Black);
	background.setOutlineColor(sf::Color::White);
	background.setOutlineThickness(2.f);
	progress.setPosition(position.left, position.top);
	progress.setFillColor(sf::Color::Blue);
}

void EnergyBar::Draw(sf::RenderWindow & window)
{
	progress.setSize(sf::Vector2f(background.getSize().x * GameObjectManager::getInstance().player->energy, background.getSize().y));
	window.draw(background);
	window.draw(progress);
}
