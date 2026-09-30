#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "GameObject.h"
#include "table.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsComponent.h"

//@desc Mushroom gameobject to bounce the ball back.
//--------------------------------------------------------------------------------------------------
class Mushroom : public GameObject
{
public:
	Mushroom(float x, float y, float radius);
	~Mushroom();
	void update(float deltaTime);
	void render(CTable* gTable, std::map<std::string, GameObject*> gm);

	std::vector<CLineSegment> _lines;
	std::vector<int> _lineIndex;
private:
	TransformComponent* t;
	RigidBodyComponent* r;
	PhysicsComponent* p;
};
#endif 