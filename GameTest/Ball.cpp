#include "stdafx.h"
//------------------------------------------------------------------------
#include <iostream>
#include <string>
//------------------------------------------------------------------------
#include "Ball.h"
#include "app\app.h"
//------------------------------------------------------------------------

//@desc Constructor where i init all the components and give them default values. Also add then to a vector of GameComponents to help loop thourgh all of them.
//--------------------------------------------------------------------------------------------------
Ball::Ball(float x, float y, float radius)
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

//@desc Helper function when the game just starts to enable velocity and make sure its our first time laucnh. Basically launch the ball.
//--------------------------------------------------------------------------------------------------
void Ball::launch() {
	if (r->bIsFirstTimeLuanch) {
		r->bIsFirstTimeLuanch = false;
		r->_bGravityEnable = true;
		r->_velocity.m_y = 0.5;
	}
}

//@desc Updater where if this gameobject has any children they would all update
//--------------------------------------------------------------------------------------------------
void Ball::update(float deltaTime)
{
	//Update Score
	score = p->score;

	//Gravity
	if(r->_bGravityEnable)
		r->_acceleration.m_y = r->_gravity;

	r->_velocity = r->_velocity + r->_acceleration * deltaTime;

	//Clamp Velocity and Acceleration
	checkVelocityClamp(0.5f, 0.5f);

	t->_position = t->_position + r->_velocity * deltaTime;

	r->_angularVelocity += r->_angularAcceleration * deltaTime;
	t->_rotation += r->_angularVelocity * deltaTime;

	r->_acceleration.m_x = 0.0f;
	r->_acceleration.m_y = 0.0f;
	r->_angularAcceleration = 0.0f;

	GameObject::update(deltaTime);
}

//@desc Renderer where if this gameobject has any children they would all render
//--------------------------------------------------------------------------------------------------
void Ball::render(CTable* gTable, std::map<std::string, GameObject*> gm)
{
	//Display Score Text
	char textBuffer[256];
	sprintf(textBuffer, "Pinball game");
	App::Print(20.0f, 715.0f, textBuffer, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_8_BY_13);

	char textBuffer1[256];
	sprintf(textBuffer1, "Score:  %0.1f", score);
	App::Print(20.0f, 700.0f, textBuffer1, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_8_BY_13);

	char textBuffer2[256];
	sprintf(textBuffer2, "How to play: ");
	App::Print(20.0f, 650.0f, textBuffer2, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_8_BY_13);

	char textBuffer3[256];
	sprintf(textBuffer3, "A and D to move paddles");
	App::Print(20.0f, 635.0f, textBuffer3, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_8_BY_13);

	char textBuffer4[256];
	sprintf(textBuffer4, "R to restart. Space to Laucnh.");
	App::Print(20.0f, 620.0f, textBuffer4, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_8_BY_13);

	if (p->CollisionCheck(gTable, gm)) {
		p->CollisionResolve(this, 0.9f);
	}

	int centerX = t->_position.m_x;
	int centerY = t->_position.m_y;
	int radius = p->radius;
	for (int i = 0; i < 360; i += 30)
	{
		double toRadians = (double)i / 180.0 * PI;
		double angle = 30.0 / 180.0 * PI;
		float rotationInRad = t->_rotation / 180.0f * PI;
		CLineSegment line;
		line.m_type = eLine_Ball;
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

//@desc To make sure velocity doesn't go to crazy when bouncing around
//--------------------------------------------------------------------------------------------------
void Ball::checkVelocityClamp(float maxVelocityX, float maxVelocityY) {
	if (r->_velocity.m_x > maxVelocityX) {
		r->_velocity.m_x = maxVelocityX;
	}

	if (r->_velocity.m_x > maxVelocityY) {
		r->_velocity.m_x = maxVelocityY;
	}
}

//@desc Deconstrutor
//--------------------------------------------------------------------------------------------------
Ball::~Ball()
{
	delete t;
	delete r;
	delete p;
}