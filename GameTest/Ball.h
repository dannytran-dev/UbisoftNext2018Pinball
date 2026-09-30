#ifndef BALL1_H
#define BALL1_H

#include "table.h"
#include "GameObject.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsComponent.h"

//@desc Ball gameobject.
//--------------------------------------------------------------------------------------------------
class Ball : public GameObject
{
public:
	float score = 0.0f;
	bool bIsFirstTimeLuanch = true;

	Ball(float x, float y, float radius);
	~Ball();

	void launch();
	void update(float deltaTime);
	void render(CTable* gTable, std::map<std::string, GameObject*> gm);
	void checkVelocityClamp(float maxVelocityX, float maxVelocityY);

	std::vector<CLineSegment> _lines;
	std::vector<int> _lineIndex;
private:
	TransformComponent* t;
	RigidBodyComponent* r;
	PhysicsComponent* p;
};
#endif 