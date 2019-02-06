/*
GameObjectManager.hpp - singleton for adding and deleting game objects
*/

#ifndef go_manager_hpp_
#define go_manager_hpp_

#include "Game.hpp"
#include <vector>

class GameObjectManager
{
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
public:
	void AddGameObject(std::unique_ptr<GameObject> gameObject)
	{
		AddedGameObjects.push_back(std::move(gameObject));
	}
	void RemoveGameObject(GameObject* gameObject) {
		RemovedGameObjects.push_back(gameObject);
	}
};
#endif