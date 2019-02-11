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

PausedText::PausedText(const sf::Font & font) : overlay(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))
{
	overlay.setFillColor(sf::Color(0, 0, 0, 100));
	text.setFont(font);
	text.setString("paused");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
}

void PausedText::Draw(sf::RenderWindow & window)
{
	// center text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));

	window.draw(overlay);
	window.draw(text);
}

ScoreText::ScoreText(sf::Rect<int> position, const sf::Font & font) 
	//: background(sf::Vector2f(position.width, position.height))
{
	//background.setPosition(position.left, position.top);
	//background.setFillColor(sf::Color::Black);

	text.setFont(font);
	text.setString("0000");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::White);
	text.setPosition(position.left + 10, position.top + 10);
}

void ScoreText::Draw(sf::RenderWindow & window)
{
	std::ostringstream ss;
	ss << std::setw(4) << std::setfill('0') << GameObjectManager::getInstance().player->Score;
	text.setString(ss.str());
	//window.draw(background);
	window.draw(text);
}
