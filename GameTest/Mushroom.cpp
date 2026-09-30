#include "stdafx.h"
//------------------------------------------------------------------------
#include <iostream>
#include <string>
//------------------------------------------------------------------------
#include "Mushroom.h"
#include "app\app.h"
//------------------------------------------------------------------------

//@desc Constructor where i init all the components and give them default values. Also add then to a vector of GameComponents to help loop thourgh all of them.
//--------------------------------------------------------------------------------------------------
Mushroom::Mushroom(float x, float y, float radius)
{
	t = new TransformComponent();
	t->_position = CPoint();
	t->_position.m_x = x;
	t->_position.m_y = y;
	t->_rotation = 0.0f;

	r = new RigidBodyComponent();
	r->_velocity = CPoint();
	r->_velocity.m_x = 0.0;
	r->_velocity.m_y = 0.0;
	r->_angularVelocity = 0.0f;

	p = new PhysicsComponent();
	p->radius = radius;

	this->addComponent(t);
	this->addComponent(r);
	this->addComponent(p);
}

//@desc Updater where if this gameobject has any children they would all update
//--------------------------------------------------------------------------------------------------
void Mushroom::update(float deltaTime)
{
	GameObject::update(deltaTime);
}

//@desc Renderer where if this gameobject has any children they would all render
//--------------------------------------------------------------------------------------------------
void Mushroom::render(CTable* gTable, std::map<std::string, GameObject*> gm)
{
	int centerX = t->_position.m_x;
	int centerY = t->_position.m_y;
	int radius = p->radius;
	for (int i = 0; i < 360; i += 45)
	{
		double toRadians = (double)i / 180.0 * PI;
		double angle = 45.0 / 180.0 * PI;
		float rotationInRad = t->_rotation / 180.0f * PI;
		CLineSegment line;
		line.m_type = eLine_Mushroom;
		line.m_start.m_x = radius * cos(toRadians);
		line.m_start.m_y = radius * sin(toRadians);
		line.m_end.m_x = radius * cos(toRadians + angle);
		line.m_end.m_y = radius * sin(toRadians + angle);
		_lines.push_back(line);
		_lineIndex.push_back(gTable->m_lines.size());
		gTable->m_lines.push_back(line);
	}

	for (int i = 0; i < _lineIndex.size(); i++)
	{
		int index = _lineIndex[i];
		if (index < gTable->m_lines.size())
		{
			float rotationInRad = t->_rotation / 180.0f * PI;
			gTable->m_lines[index].m_start.m_x = t->_position.m_x + (_lines[i].m_start.m_x * cos(rotationInRad) - _lines[i].m_start.m_y * sin(rotationInRad));
			gTable->m_lines[index].m_start.m_y = t->_position.m_y + (_lines[i].m_start.m_x * sin(rotationInRad) + _lines[i].m_start.m_y * cos(rotationInRad));
			gTable->m_lines[index].m_end.m_x = t->_position.m_x + (_lines[i].m_end.m_x * cos(rotationInRad) - _lines[i].m_end.m_y * sin(rotationInRad));
			gTable->m_lines[index].m_end.m_y = t->_position.m_y + (_lines[i].m_end.m_x * sin(rotationInRad) + _lines[i].m_end.m_y * cos(rotationInRad));
		}
	}
	GameObject::render(gTable, gm);
}

//@desc Deconstrutor
//--------------------------------------------------------------------------------------------------
Mushroom::~Mushroom()
{	
}