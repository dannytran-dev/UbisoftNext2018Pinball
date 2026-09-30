#ifndef BENGINE_GAMEOBJECT_H
#define BENGINE_GAMEOBJECT_H

#include "stdafx.h"
#include "table.h"
#include "map"

#include <string>
#include <vector>

//@desc My most important class to help manage all game components and game objects.
//--------------------------------------------------------------------------------------------------
class GameComponent;

class  GameObject
{
public:
	int m_id;

	std::vector<GameObject*> m_children;         //GameObject has ownership of its children
	std::vector<GameComponent*> m_components;    //GameObject has ownership of its GameComponents

	GameObject();
	virtual ~GameObject();

	void setID(int id);
	void addComponent(GameComponent* component);
	void addChild(GameObject* child);
	void insertChild(GameObject* child, int position);
	void removeChild(int index);

	int getID() const;

	int getNumComponents() const;
	int getNumChildren() const;

	template<class T>
	T* getComponent()
	{
		T* ret = 0;
		for (int i = 0; i < m_components.size(); i++)
		{
			ret = dynamic_cast<T*>(m_components[i]);
			if (ret != 0)
				break;
		}

		return ret;
	}

	template<class T>
	void removeComponent()
	{
		T* comp = 0;
		for (int i = 0; i < m_components.size(); i++)
		{
			comp = dynamic_cast<T*>(m_components[i]);
			if (ret != 0)
			{
				delete comp;
				m_components.erase(m_components.begin() + i);
				return;
			}
		}
	}

	GameObject* getChild(int index);

	virtual void init();
	virtual void update(float deltaTime);
	virtual void render(CTable* gTable, std::map<std::string, GameObject*> gm);

protected:
private:
};

class GameComponent
{
	GameObject* m_gameObject;

public:
	GameComponent();
	virtual ~GameComponent();

	void attachToGameObject(GameObject* gameObject);
	GameObject* getGameObject() const;

	virtual void init();
	virtual void update(float deltaTime);

protected:
private:
};

#endif //BENGINE_GAMEOBJECT_H