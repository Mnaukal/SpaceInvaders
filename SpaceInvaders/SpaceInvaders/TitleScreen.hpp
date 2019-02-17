/*
TitleScreen.hpp - shown before game starts
*/

#ifndef title_hpp_
#define title_hpp_

#include "Game.hpp"
#include "InvadersConstants.hpp"
#include "Invaders.hpp"
#include <iostream>

class MenuItem;

class TitleScreen : public Game {
private:
	sf::Font font;
	sf::Text title, subtitle;
	bool loadGame = false;
	std::vector<MenuItem> menu;
	unsigned selectedItem = 0;
	std::string custom_difficulty;
	bool enteringText = false;
	void SelectItem(int item);
	void StartEnteringText();
	void StopEnteringText();
public:
	TitleScreen();
	TitleScreen(const std::string & display_text);
	// Inherited via Game
	virtual void Update(sf::Time deltaTime) override {};
	virtual void Draw(sf::RenderWindow & window) override;
	virtual bool HandleEvent(const sf::Event & event) override;
	virtual void Pause() override {};
	virtual void Resume() override {};
	virtual void SaveAndExit() override {};
	virtual sf::View Resize(unsigned width, unsigned height) override;
	virtual bool WantLoadLevel() override { return loadGame; }
	virtual std::unique_ptr<Game> LoadLevel() override;
};

class MenuItem : public GameObject {
private:
	sf::Text text;
	sf::RectangleShape background;
	float min_width;
public:
	MenuItem(const std::string & text, sf::Rect<float> position, const sf::Font & font);
	bool selected = false;
	void setString(const std::string & text);
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime) override {};
	virtual sf::Rect<float> BoundingBox() override;
};
#endif