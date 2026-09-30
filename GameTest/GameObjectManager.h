#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "GameObject.h"

#include <map>
#include <algorithm>

//@desc Game object manager helps update all gameobject that i have in scene.
//--------------------------------------------------------------------------------------------------
class GameObjectManager
{
public:
	std::map<std::string, GameObject*> _gameObjects;

	GameObjectManager();
	~GameObjectManager();

	void addChild(std::string name, GameObject* gameObject);
	void removeChild(std::string name);
	int getNumChildren() const;
	GameObject* Get(std::string name) const;

	void update(float deltaTime);
	void render(CTable* gTable, std::map<std::string, GameObject*> gm);

protected:
private:
	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, GameObject*> & p) const
		{
			delete p.second;
		}
	};
};
#endif 