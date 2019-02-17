#include "UserInterface.hpp"

EnergyBar::EnergyBar(sf::Rect<int> position) : background(sf::Vector2f(position.width, position.height)), progress(sf::Vector2f(position.width, position.height))
{
	background.setPosition((float)position.left, (float)position.top);
	background.setFillColor(sf::Color::Black);
	background.setOutlineColor(sf::Color::White);
	background.setOutlineThickness(2.f);
	progress.setPosition((float)position.left, (float)position.top);
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
	text.setPosition((float)position.left, (float)position.top);
}

void ScoreText::Draw(sf::RenderWindow & window)
{
	std::ostringstream ss;
	ss << std::setw(4) << std::setfill('0') << GameObjectManager::getInstance().player->Score;
	text.setString(ss.str());
	//window.draw(background);
	window.draw(text);
}

LivesDisplay::LivesDisplay(const sf::Texture & heart, const sf::Texture & heart_empty)
	: hearts(PLAYER_LIVES), heart(heart), heart_empty(heart_empty)
{
	for (size_t i = 0; i < hearts.size(); i++)
	{
		hearts[i].setPosition((float)i * 44 + 10, 10.f);
		hearts[i].setScale(3, 3);
	}
}

void LivesDisplay::Draw(sf::RenderWindow & window)
{
	for (size_t i = 0; i < hearts.size() && i < GameObjectManager::getInstance().player->lives; i++)
	{
		hearts[i].setTexture(heart);
		window.draw(hearts[i]);
	}
	for (size_t i = GameObjectManager::getInstance().player->lives; i < hearts.size(); i++)
	{
		hearts[i].setTexture(heart_empty);
		window.draw(hearts[i]);
	}
}

GameOverText::GameOverText(const sf::Font & font) : overlay(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))
{
	overlay.setFillColor(sf::Color(64, 0, 0, 180));
	text.setFont(font);
	text.setString("game over");
	text.setCharacterSize(70);
	text.setFillColor(sf::Color::White);
	score.setFont(font);
	score.setString("0000");
	score.setCharacterSize(40);
	score.setFillColor(sf::Color::White);
}

void GameOverText::Draw(sf::RenderWindow & window)
{
	// center text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, 300.f));
	// center score text
	sf::FloatRect scoreRect = score.getLocalBounds();
	score.setOrigin(scoreRect.left + scoreRect.width / 2.0f,
		scoreRect.top + scoreRect.height / 2.0f);
	score.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, 400.f));

	window.draw(overlay);
	window.draw(text);
	score.setString(std::to_string(GameObjectManager::getInstance().player->Score));
	window.draw(score);
}
