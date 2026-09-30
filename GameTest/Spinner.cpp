#include "stdafx.h"
//------------------------------------------------------------------------
#include <iostream>
#include <string>
//------------------------------------------------------------------------
#include "Spinner.h"
#include "app\app.h"
//------------------------------------------------------------------------

//@desc Constructor where i init all the components and give them default values. Also add then to a vector of GameComponents to help loop thourgh all of them.
//--------------------------------------------------------------------------------------------------
Spinner::Spinner(float x, float y)
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

	this->addComponent(t);
	this->addComponent(r);
	this->addComponent(p);
}

//@desc Updater where if this gameobject has any children they would all update. This is where i apply the rotation to have the line spinning.
//--------------------------------------------------------------------------------------------------
void Spinner::update(float deltaTime)
{
	GameObject::update(deltaTime);

	Constraints();

	r->_angularVelocity = r->_angularAcceleration * deltaTime;
	t->_rotation += r->_angularVelocity * deltaTime;
}

//@desc Renderer where if this gameobject has any children they would all render
//--------------------------------------------------------------------------------------------------
void Spinner::render(CTable* gTable, std::map<std::string, GameObject*> gm)
{
	CLineSegment l1;
	l1.m_type = eLine_Spinner;
	l1.m_start.m_x = -25;
	l1.m_start.m_y = 0;
	l1.m_end.m_x = 25;
	l1.m_end.m_y = 0;
	_lines.push_back(l1);
	_lineIndex.push_back(gTable->m_lines.size());
	gTable->m_lines.push_back(l1);

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

//@desc To help make sure the spinners dont spin to fast
//--------------------------------------------------------------------------------------------------
void Spinner::Constraints()
{
	if(r->_angularAcceleration <  0.05f)
		r->_angularAcceleration += 0.001f;
}

//@desc Deconstrutor
//--------------------------------------------------------------------------------------------------
Spinner::~Spinner()
{

}