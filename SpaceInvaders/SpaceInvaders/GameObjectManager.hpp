/*
GameObjectManager.hpp - singleton for game object data
*/

#ifndef go_manager_hpp_
#define go_manager_hpp_

class Player;

#include "Game.hpp"
#include "Player.hpp"
#include <vector>

class GameObjectManager
{
	// singleton
public:
	static GameObjectManager& getInstance()
	{
		static GameObjectManager    instance; 
		return instance;
	}
	GameObjectManager(GameObjectManager const&) = delete;
	void operator=(GameObjectManager const&) = delete;
private:
	GameObjectManager() {}

	friend class Invaders;
protected:
	std::vector<std::unique_ptr<GameObject>> AddedGameObjects;
	std::vector<GameObject*> RemovedGameObjects;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	std::vector<std::unique_ptr<GameObject>> UIobjects;
	void AddGameObjects();
	void RemoveGameObjects();
	void ClearAll();
public:
	Player* player;
	void AddGameObject(std::unique_ptr<GameObject> gameObject)
	{
		AddedGameObjects.push_back(std::move(gameObject));
	}
	void RemoveGameObject(GameObject* gameObject) {
		RemovedGameObjects.push_back(gameObject);
	}
	void AddUIObject(std::unique_ptr<GameObject> gameObject); 
	void RemoveUIObject(GameObject* gameObject);
	void Update();
};
#endif