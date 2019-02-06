#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Invaders.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Space Invaders!");
	sf::Clock clock;
	std::unique_ptr<Game> game = std::make_unique<Invaders>();

	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		game->Update(elapsed);

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				game->SaveAndExit();
				window.close();
				break;
			case sf::Event::Resized:
			{
				// TODO
				if (window.getSize().x == event.size.width) // changed height
					event.size.width = event.size.height * 16 / 9;
				else
					event.size.height = event.size.width * 9 / 16;

				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
				//sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				//window.setView(sf::View(visibleArea));
				window.setSize(sf::Vector2u(event.size.width, event.size.height));
			}
				break;
			case sf::Event::LostFocus:
				game->Pause();
				break;
			case sf::Event::GainedFocus:
				game->Resume();
				break;
			default:
				game->HandleEvent(event);
				break;
			}
		}

		window.clear();
		game->Draw(window);
		window.display();
	}

	return 0;
}