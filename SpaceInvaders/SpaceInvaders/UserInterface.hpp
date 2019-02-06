/*
UserInterface.hpp - code UI overlay
*/

#ifndef ui_hpp_
#define ui_hpp_

#include "Game.hpp"
#include "GameObjectManager.hpp"



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

#endif