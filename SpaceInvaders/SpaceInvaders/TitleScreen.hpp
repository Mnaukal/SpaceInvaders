/*
TitleScreen.hpp - shown before game starts
*/

#ifndef title_hpp_
#define title_hpp_

#include "Game.hpp"
#include "InvadersConstants.hpp"
#include "Invaders.hpp"
#include <iostream>

class TitleScreen : public Game {
private:
	sf::Font font;
	sf::Text title, subtitle;
	bool loadGame = false;
public:
	TitleScreen();
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



#endif