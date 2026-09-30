#include "stdafx.h"
//------------------------------------------------------------------------
#include <iostream>
#include <string>
//------------------------------------------------------------------------
#include "FlippersLeft.h"
#include "app\app.h"
//------------------------------------------------------------------------

//@desc Constructor where i init all the components and give them default values. Also add then to a vector of GameComponents to help loop thourgh all of them.
//--------------------------------------------------------------------------------------------------
FlippersLeft::FlippersLeft(float x, float y)
{
	t = new TransformComponent();
	t->_position = CPoint();
	t->_position.m_x = x;
	t->_position.m_y = y;
	t->_rotation = 15.0f;

	r = new RigidBodyComponent();
	r->_velocity = CPoint();
	r->_velocity.m_x = 0.0;
	r->_velocity.m_y = 0.0;
	r->_angularVelocity = 0.0f;

	p = new PhysicsComponent();

	this->addComponent(t);
	this->addComponent(r);
	this->addComponent(p);
}

//@desc Updater where if this gameobject has any children they would all update
//--------------------------------------------------------------------------------------------------
void FlippersLeft::update(float deltaTime)
{
	GameObject::update(deltaTime);

	r->_velocity = r->_velocity + r->_acceleration * deltaTime;
	t->_position = t->_position + r->_velocity * deltaTime;

	r->_angularVelocity += r->_angularAcceleration * deltaTime;
	t->_rotation += r->_angularVelocity * deltaTime;

	r->_acceleration.m_x = 0.0f;
	r->_acceleration.m_y = 0.0f;
	r->_angularAcceleration = 0.0f;

	Constraints();
}

//@desc Renderer where if this gameobject has any children they would all render
//--------------------------------------------------------------------------------------------------
void FlippersLeft::render(CTable* gTable, std::map<std::string, GameObject*> gm)
{
	GameObject::render(gTable, gm);

	CLineSegment l1;
	l1.m_type = eLine_Flipper;
	l1.m_start.m_x = 0;
	l1.m_start.m_y = 0;
	l1.m_end.m_x = 125;
	l1.m_end.m_y = 0;
	_lines.push_back(l1);
	_lineIndex.push_back(gTable->m_lines.size());
	gTable->m_lines.push_back(l1);

	CLineSegment l2;
	l2.m_type = eLine_Flipper;
	l2.m_start.m_x = 0;
	l2.m_start.m_y = 20;
	l2.m_end.m_x = 125;
	l2.m_end.m_y = 0;
	_lines.push_back(l2);
	_lineIndex.push_back(gTable->m_lines.size());
	gTable->m_lines.push_back(l2);

	CLineSegment l3;
	l3.m_type = eLine_Flipper;
	l3.m_start.m_x = 0;
	l3.m_start.m_y = 0;
	l3.m_end.m_x = 0;
	l3.m_end.m_y = 20;
	_lines.push_back(l3);
	_lineIndex.push_back(gTable->m_lines.size());
	gTable->m_lines.push_back(l3);

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
}

//@desc To help make sure the paddles dont go past a certain angle
//--------------------------------------------------------------------------------------------------
void FlippersLeft::Constraints()
{
	r->_angularAcceleration -= 0.001f;
	if (t->_rotation < -15.0f)
	{
		t->_rotation = -15.0f;
		r->_angularVelocity = 0.0f;
	}
	else if (t->_rotation > 15.0f)
	{
		t->_rotation = 15.0f;
		r->_angularVelocity = 0.0f;
	}
}

//@desc Deconstrutor
//--------------------------------------------------------------------------------------------------
FlippersLeft::~FlippersLeft()
{
	delete t;
	delete r;
	delete p;
}