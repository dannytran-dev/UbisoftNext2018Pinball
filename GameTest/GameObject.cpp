#include "stdafx.h"
#include "GameObject.h"
#include <vector>

//@desc Constructor initalise the two vectors
//--------------------------------------------------------------------------------------------------
GameObject::GameObject() : m_id(0)
{
	m_children = std::vector<GameObject*>();
	m_components = std::vector<GameComponent*>();
}

//@desc To set the id of each gameobject
//--------------------------------------------------------------------------------------------------
void GameObject::setID(int id)
{
	m_id = id;
}

//@desc Add component into the vector of the gameobject
//--------------------------------------------------------------------------------------------------
void GameObject::addComponent(GameComponent* component)
{
	m_components.push_back(component);
	component->attachToGameObject(this);
}

//@desc Adds gameobject child
//--------------------------------------------------------------------------------------------------
void GameObject::addChild(GameObject* child)
{
	m_children.push_back(child);
}

//@desc To insert into certain positions of the vector
//--------------------------------------------------------------------------------------------------
void GameObject::insertChild(GameObject* child, int position)
{
	if (position < 0 || position > m_children.size())
	{
		
	}

	m_children.insert(m_children.begin() + position, child);
}

//@desc remove child at index
//--------------------------------------------------------------------------------------------------
void GameObject::removeChild(int index)
{
	if (index >= 0 && index < m_children.size())
	{
		GameObject* child = m_children[index];
		delete child;
		m_children.erase(m_children.begin() + index);
	}
}

//@desc Getters and setters
//--------------------------------------------------------------------------------------------------
int GameObject::getID() const
{
	return m_id;
}

int GameObject::getNumComponents() const
{
	return m_components.size();
}

int GameObject::getNumChildren() const
{
	return m_children.size();
}

GameObject* GameObject::getChild(int index)
{
	return m_children[index];
}

//@desc All children of this gameobject init is called
//--------------------------------------------------------------------------------------------------
void GameObject::init()
{
	//Start all of my GameComponents
	std::vector<GameComponent*>::iterator comp;
	for (comp = m_components.begin(); comp != m_components.end(); comp++)
	{
		(*comp)->init();
	}

	//Start all of my children
	std::vector<GameObject*>::iterator child;
	for (child = m_children.begin(); child != m_children.end(); child++)
	{
		(*child)->init();
	}
}

//@desc All children update gets called
//--------------------------------------------------------------------------------------------------
void GameObject::update(float deltaTime)
{
	//Update all of my GameComponents
	std::vector<GameComponent*>::iterator comp;
	for (comp = m_components.begin(); comp != m_components.end(); comp++)
	{
		(*comp)->update(deltaTime);
	}

	//Update all of my children
	std::vector<GameObject*>::iterator child;
	for (child = m_children.begin(); child != m_children.end(); child++)
	{
		(*child)->update(deltaTime);
	}
}

//@desc All children render get called
//--------------------------------------------------------------------------------------------------
void GameObject::render(CTable* gTable, std::map<std::string, GameObject*> gm)
{
	//Update all of my children
	std::vector<GameObject*>::iterator child;
	for (child = m_children.begin(); child != m_children.end(); child++)
	{
		(*child)->render(gTable, gm);
	}
}

//@desc Deconstrutor
//--------------------------------------------------------------------------------------------------
GameObject::~GameObject()
{
	//Must delete all GameComponents
	for (int i = 0; i < m_components.size(); i++)
	{
		delete m_components[i];
	}
	m_components.clear();

	//Must delete all children GameObjects
	for (int i = 0; i < m_children.size(); i++)
	{
		delete m_children[i];
	}
	m_children.clear();
}

GameComponent::GameComponent() : m_gameObject(0) {}

//@desc Attach gameobject to gameobject
//--------------------------------------------------------------------------------------------------
void GameComponent::attachToGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

//@desc Getters for gameobject to get their parent gameobject
//--------------------------------------------------------------------------------------------------
GameObject* GameComponent::getGameObject() const
{
	return m_gameObject;
}
//@desc just in case we need to update components
//--------------------------------------------------------------------------------------------------
void GameComponent::init() {}
void GameComponent::update(float deltaTime) {}

//@desc Deconstrutor
//--------------------------------------------------------------------------------------------------
GameComponent::~GameComponent() {}
