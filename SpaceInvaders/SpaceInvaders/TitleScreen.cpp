#include "TitleScreen.hpp"

void TitleScreen::SelectItem(int item)
{
	if (item < 0)
		item = menu.size() - 1;
	if (item >= menu.size())
		item = 0;
	selectedItem = item;

	for (size_t i = 0; i < menu.size(); i++)
	{
		menu[i].selected = false;
	}
	menu[item].selected = true;

	if (selectedItem != 3)
		StopEnteringText();
}

void TitleScreen::StartEnteringText()
{
	enteringText = true;
	custom_difficulty = "";
	menu[3].setString("");
}

void TitleScreen::StopEnteringText()
{
	enteringText = false;
	menu[3].setString("custom");
}

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
	title.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, 150));

	subtitle.setFont(font);
	subtitle.setString("press space to play");
	subtitle.setCharacterSize(40);
	subtitle.setFillColor(sf::Color::White);
	//center text
	sf::FloatRect subtitleTextRect = subtitle.getLocalBounds();
	subtitle.setOrigin(subtitleTextRect.left + subtitleTextRect.width / 2.0f,
		subtitleTextRect.top + subtitleTextRect.height / 2.0f);
	subtitle.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, 650));

	menu.push_back(MenuItem("easy", sf::Rect<float>(SCREEN_WIDTH / 2.f - 150, 300, 300, 50), font));
	menu.push_back(MenuItem("hard", sf::Rect<float>(SCREEN_WIDTH / 2.f - 150, 360, 300, 50), font));
	menu.push_back(MenuItem("expert", sf::Rect<float>(SCREEN_WIDTH / 2.f - 150, 420, 300, 50), font));
	menu.push_back(MenuItem("custom", sf::Rect<float>(SCREEN_WIDTH / 2.f - 150, 480, 300, 50), font));
	SelectItem(0);
}

TitleScreen::TitleScreen(const std::string & display_text) : TitleScreen()
{
	subtitle.setString(display_text);
	subtitle.setCharacterSize(40);
	subtitle.setFillColor(sf::Color(255, 153, 153, 255));
	//center text
	sf::FloatRect subtitleTextRect = subtitle.getLocalBounds();
	subtitle.setOrigin(subtitleTextRect.left + subtitleTextRect.width / 2.0f,
		subtitleTextRect.top + subtitleTextRect.height / 2.0f);
	subtitle.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, 650));
}

void TitleScreen::Draw(sf::RenderWindow & window)
{
	window.draw(title);
	window.draw(subtitle);

	if (enteringText)
		menu[3].setString(custom_difficulty);

	for (auto && m : menu)
	{
		m.Draw(window);
	}
}

bool TitleScreen::HandleEvent(const sf::Event & event)
{
	if (enteringText && event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == '\b')
		{
			if (custom_difficulty.size() > 0)
				custom_difficulty.pop_back();
		}
		else if(event.text.unicode >= 97 && event.text.unicode <= 122) // small letters only
			custom_difficulty += event.text.unicode;
		std::cout << custom_difficulty << std::endl;
	}

	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter)
		{
			if (selectedItem == 3)
			{
				if (enteringText)
					loadGame = true;
				else
					StartEnteringText();
			}
			else
				loadGame = true;
		}
		if (event.key.code == sf::Keyboard::Up)
			SelectItem(selectedItem - 1);
		if (event.key.code == sf::Keyboard::Down)
			SelectItem(selectedItem + 1);
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

	if(selectedItem == 0)
		return std::make_unique<Invaders>("easy.txt"); 
	if (selectedItem == 1)
		return std::make_unique<Invaders>("hard.txt");
	if (selectedItem == 2)
		return std::make_unique<Invaders>("expert.txt");
	if (selectedItem == 3)
		return std::make_unique<Invaders>(custom_difficulty + ".txt"); 

	return nullptr;
}

MenuItem::MenuItem(const std::string & text_str, sf::Rect<float> position, const sf::Font & font) 
	: min_width(position.width)
{
	background.setOrigin(position.width / 2, position.height / 2);
	background.setPosition(position.left + position.width / 2, position.top + position.height / 2);
	background.setSize(sf::Vector2f(position.width, position.height));
	text.setFont(font);
	text.setString(text_str);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::White);

	// center text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(position.left + position.width / 2.0f, position.top + position.height/ 2.0f));
}

void MenuItem::setString(const std::string & text_str)
{
	text.setString(text_str);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	float w = std::max(min_width, textRect.width + 30);
	background.setScale(w / min_width, 1);
}

void MenuItem::Draw(sf::RenderWindow & window)
{
	if (selected)
		background.setFillColor(sf::Color(20, 20, 20, 255));
	else
		background.setFillColor(sf::Color::Black);

	window.draw(background);
	window.draw(text);
}

sf::Rect<float> MenuItem::BoundingBox()
{
	return sf::Rect<float>();
}
