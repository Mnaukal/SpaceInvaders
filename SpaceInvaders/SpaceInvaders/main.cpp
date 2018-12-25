#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Invaders.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Space Invaders!");
	sf::Clock clock;
	std::unique_ptr<Game> game = std::make_unique<Invaders>();

	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		game->Update(elapsed);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (game->HandleEvent(event))
				continue;

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
			{
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
				break;
			case sf::Event::LostFocus:
				std::cout << "Pause" << std::endl;
				break;
			case sf::Event::GainedFocus:
				std::cout << "Resume" << std::endl;
				break;
			default:
				break;
			}
		}

		window.clear();
		game->Draw(window);
		window.display();
	}

	return 0;
}