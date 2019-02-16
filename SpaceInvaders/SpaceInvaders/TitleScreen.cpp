#include "TitleScreen.hpp"

TitleScreen::TitleScreen()
{
	if (!font.loadFromFile(FONT_PATH))
	{
		std::cout << "Error loading font" << std::endl;
	}

	title.setFont(font);
	title.setString("space invaders");
	title.setCharacterSize(90);
	title.setFillColor(sf::Color::White);
	//center text
	sf::FloatRect titleTextRect = title.getLocalBounds();
	title.setOrigin(titleTextRect.left + titleTextRect.width / 2.0f,
		titleTextRect.top + titleTextRect.height / 2.0f);
	title.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, 200));

	subtitle.setFont(font);
	subtitle.setString("press space to play");
	subtitle.setCharacterSize(40);
	subtitle.setFillColor(sf::Color::White);
	//center text
	sf::FloatRect subtitleTextRect = subtitle.getLocalBounds();
	subtitle.setOrigin(subtitleTextRect.left + subtitleTextRect.width / 2.0f,
		subtitleTextRect.top + subtitleTextRect.height / 2.0f);
	subtitle.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, 350));
}

void TitleScreen::Draw(sf::RenderWindow & window)
{
	window.draw(title);
	window.draw(subtitle);
}

bool TitleScreen::HandleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			loadGame = true;
		}
	}

	return false;
}

sf::View TitleScreen::Resize(unsigned width, unsigned height)
{
	return sf::View();
}

std::unique_ptr<Game> TitleScreen::LoadLevel()
{
	if (!loadGame)
		return nullptr;

	return std::make_unique<Invaders>("easy.txt"); // TODO
}
