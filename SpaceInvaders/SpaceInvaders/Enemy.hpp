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
protected:
	int width, height;
	int killScore = 100;
	bool did_hit = false;
	void HitPlayerOnce();
public:
	float Speed = ENEMY_SPEED;
	Enemy(const sf::Texture & texture);
	Enemy(const sf::Texture & texture, float speed) : Enemy(texture) { Speed = speed; };
	virtual void RemoveEnemy(); // removes enemy
	virtual int EnemyScore() = 0; // score points for killing
	// Inherited via GameObject
	virtual void Draw(sf::RenderWindow & window) override;
	virtual sf::Rect<float> BoundingBox() override;
	virtual void Collide(GameObject* other, sf::FloatRect intersection) override;
};
#endif

