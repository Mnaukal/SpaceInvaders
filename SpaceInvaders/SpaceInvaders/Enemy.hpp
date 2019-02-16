/*
Enemy.hpp - common code for enemies
*/

#ifndef enemy_hpp_
#define enemy_hpp_

#include "Game.hpp"
#include "InvadersConstants.hpp"
#include "GameObjectManager.hpp"

class Enemy : public GameObject
{
private:
	sf::Sprite sprite;
	int width, height;
public:
	float Speed = ENEMY_SPEED;
	Enemy(const sf::Texture & texture);
	Enemy(const sf::Texture & texture, float speed) : Enemy(texture) { Speed = speed; };
	virtual void RemoveEnemy();
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual sf::Rect<float> BoundingBox() override;
};
#endif

