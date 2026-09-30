#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "table.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsComponent.h"

#include "FlippersLeft.h"
#include "FlippersRight.h"
#include "Ball.h"

//@desc Player gameobject is where all the controls are being handled. Also where we spawn the ball and two paddles in the right position. Has its own components 
//		just in case we want to adjust.
//--------------------------------------------------------------------------------------------------
class Player : public GameObject
{
public:
	int score = 0;

	Player();
	void update(float deltaTime);
	void render(CTable* gTable, std::map<std::string, GameObject*> gm);
	~Player();

	std::vector<CLineSegment> _lines;
	std::vector<int> _lineIndex;
private:
	Ball* ball1;

	FlippersLeft* flippersLeft;
	FlippersRight* flippersRight;

	TransformComponent * t;
	RigidBodyComponent* r;
	PhysicsComponent* p;
};
#endif 