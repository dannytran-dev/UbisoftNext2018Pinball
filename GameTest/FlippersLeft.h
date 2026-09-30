#ifndef FLIPPERSLEFT_H
#define FLIPPERSLEFT_H

#include "GameObject.h"
#include "table.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsComponent.h"

//@desc Left Flippers gameobject
//--------------------------------------------------------------------------------------------------
class FlippersLeft : public GameObject
{
public:
	FlippersLeft(float x, float y);
	~FlippersLeft();
	void update(float deltaTime);
	void render(CTable* gTable, std::map<std::string, GameObject*> gm);
	void FlippersLeft::Constraints();

	std::vector<CLineSegment> _lines;
	std::vector<int> _lineIndex;
private:
	TransformComponent * t;
	RigidBodyComponent* r;
	PhysicsComponent* p;
};
#endif 