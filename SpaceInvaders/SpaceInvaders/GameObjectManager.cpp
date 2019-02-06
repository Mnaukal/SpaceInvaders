#include "GameObjectManager.hpp"

void GameObjectManager::AddUIObject(std::unique_ptr<GameObject> gameObject)
{
	UIobjects.push_back(std::move(gameObject));
}

void GameObjectManager::RemoveUIObject(GameObject * gameObject)
{
	auto go = std::find_if(UIobjects.begin(), UIobjects.end(), [gameObject](const std::unique_ptr<GameObject>& p) {
		return p.get() == gameObject;
	});
	if (go == UIobjects.end()) return;

	go->swap(UIobjects.back());
	UIobjects.back().reset();
	UIobjects.pop_back();
}

void GameObjectManager::Update()
{
	RemoveGameObjects();
	AddGameObjects();
}

void GameObjectManager::AddGameObjects()
{
	for (size_t i = 0; i < AddedGameObjects.size(); i++)
	{
		gameObjects.push_back(std::move(AddedGameObjects[i]));
	}
	AddedGameObjects.clear();
}

void GameObjectManager::RemoveGameObjects()
{
	for (auto r : RemovedGameObjects)
	{
		auto go = std::find_if(gameObjects.begin(), gameObjects.end(), [r](const std::unique_ptr<GameObject>& p) {
			return p.get() == r;
		});
		if (go == gameObjects.end()) continue;

		go->swap(gameObjects.back());
		gameObjects.back().reset();
		gameObjects.pop_back();
	}
	RemovedGameObjects.clear();
}