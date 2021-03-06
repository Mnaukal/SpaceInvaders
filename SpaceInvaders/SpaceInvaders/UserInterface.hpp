/*
UserInterface.hpp - code UI overlay
*/

#ifndef ui_hpp_
#define ui_hpp_

#include "Game.hpp"
#include "GameObjectManager.hpp"
#include <sstream>
#include <iomanip>

class EnergyBar : public GameObject 
{
private:
	sf::RectangleShape background;
	sf::RectangleShape progress;
public:
	EnergyBar(sf::Rect<int> position);
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime) {};
	virtual sf::Rect<float> BoundingBox() { return sf::Rect<float>(); };
};

class PausedText : public GameObject {
private:
	sf::RectangleShape overlay;
	sf::Text text;
public:
	PausedText(const sf::Font & font);
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime) {};
	virtual sf::Rect<float> BoundingBox() { return sf::Rect<float>(); };
};

class ScoreText : public GameObject {
private: 
	//sf::RectangleShape background;
	sf::Text text;
public:
	ScoreText(sf::Rect<int> position, const sf::Font & font);
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime) {};
	virtual sf::Rect<float> BoundingBox() { return sf::Rect<float>(); };
};

class LivesDisplay : public GameObject {
private:
	std::vector<sf::Sprite> hearts;
	const sf::Texture & heart, heart_empty;
public:
	LivesDisplay(const sf::Texture & heart, const sf::Texture & heart_empty);
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime) {};
	virtual sf::Rect<float> BoundingBox() { return sf::Rect<float>(); };
};

class GameOverText : public GameObject {
private:
	sf::RectangleShape overlay;
	sf::Text text, score;
public:
	GameOverText(const sf::Font & font);
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Update(sf::Time deltaTime) {};
	virtual sf::Rect<float> BoundingBox() { return sf::Rect<float>(); };
};

#endif