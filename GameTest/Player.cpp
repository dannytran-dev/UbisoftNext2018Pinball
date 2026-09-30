#include "stdafx.h"
//------------------------------------------------------------------------
#include <iostream>
#include <string>
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "Player.h"

//@desc Constructor where i init all the components and give them default values. Also add then to a vector of GameComponents to help loop thourgh all of them.
//--------------------------------------------------------------------------------------------------

Player::Player()
{
	t = new TransformComponent();
	t->_position = CPoint();
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

	//Add Ball
	ball1 = new Ball(832, 50, 10);

	//Add Flippers to player
	flippersLeft = new FlippersLeft((APP_INIT_WINDOW_WIDTH / 2) - 145, APP_INIT_WINDOW_HEIGHT / 10);
	flippersRight = new FlippersRight((APP_INIT_WINDOW_WIDTH / 2) + 145, APP_INIT_WINDOW_HEIGHT / 10);
}

//@desc Updater where if this gameobject has any children they would all update. This also where i handle input and make sure that the balls and flippers and update/rendering
//--------------------------------------------------------------------------------------------------
void Player::update(float deltaTime)
{
	//For Reseting
	if (App::IsKeyPressed('R'))
	{
		ball1->getComponent<TransformComponent>()->_position.m_x = 832;
		ball1->getComponent<TransformComponent>()->_position.m_y = 50;
		ball1->getComponent<RigidBodyComponent>()->_velocity.m_x = 0.0f;
		ball1->getComponent<RigidBodyComponent>()->_velocity.m_y = 0.0f;
		ball1->getComponent<RigidBodyComponent>()->_angularVelocity = 0.0f;
		ball1->getComponent<RigidBodyComponent>()->bIsFirstTimeLuanch = true;
		ball1->getComponent<RigidBodyComponent>()->_bGravityEnable = false;
		ball1->getComponent<PhysicsComponent>()->score = 0.0f;
	}

	if (App::IsKeyPressed('A'))
	{
		flippersLeft->getComponent<PhysicsComponent>()->ApplyTorque(0.0025f);
	}

	if (App::IsKeyPressed('D'))
	{
		flippersRight->getComponent<PhysicsComponent>()->ApplyTorque(-0.0025f);
	}

	if (App::IsKeyPressed(VK_SPACE))
	{
		ball1->launch();
	}
	ball1->update(deltaTime);
	flippersLeft->update(deltaTime);
	flippersRight->update(deltaTime);
	GameObject::update(deltaTime);
}

//@desc Renderer where if this gameobject has any children they would all render
//--------------------------------------------------------------------------------------------------
void Player::render(CTable* gTable, std::map<std::string, GameObject*> gm)
{
	GameObject::render(gTable, gm);

	ball1->render(gTable, gm);
	flippersLeft->render(gTable, gm);
	flippersRight->render(gTable, gm);
}

//@desc Deconstrutor
//--------------------------------------------------------------------------------------------------
Player::~Player()
{
	
}