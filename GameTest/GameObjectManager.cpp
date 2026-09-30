#include "stdafx.h"
#include "GameObjectManager.h"

//@desc Construtor
//--------------------------------------------------------------------------------------------------
GameObjectManager::GameObjectManager()
{
}

//@desc Helpers to add remove children of the game object manager
//--------------------------------------------------------------------------------------------------
void GameObjectManager::addChild(std::string name, GameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, GameObject*>(name, gameObject));
}

void GameObjectManager::removeChild(std::string name)
{
	std::map<std::string, GameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

//@desc Getters and setters
//--------------------------------------------------------------------------------------------------
GameObject* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, GameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;

}

int GameObjectManager::getNumChildren() const
{
	return _gameObjects.size();
}

//@desc Update all gameobject in the scene
//--------------------------------------------------------------------------------------------------
void GameObjectManager::update(float deltaTime)
{
	//Update all of my GameComponents
	//Update all of my children
	std::map<std::string, GameObject*>::const_iterator itr =
		_gameObjects.begin();

	while (itr != _gameObjects.end())
	{
		itr->second->update(deltaTime);
		itr++;
	}
}

//@desc Render all gameobject in the scene
//--------------------------------------------------------------------------------------------------
void GameObjectManager::render(CTable* gTable, std::map<std::string, GameObject*> gm)
{
	//Update all of my children
	std::map<std::string, GameObject*>::const_iterator itr =
		_gameObjects.begin();

	while (itr != _gameObjects.end())
	{
		itr->second->render(gTable, gm);
		itr++;
	}
}

//@desc Deconstrutor
//--------------------------------------------------------------------------------------------------
GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}