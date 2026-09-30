#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "GameObject.h"
#include "table.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsComponent.h"

//@desc Teleporter gameobject to help make it shape like a triangle.
//--------------------------------------------------------------------------------------------------
class Teleporter : public GameObject
{
public:
	Teleporter(float x, float y);
	void update(float deltaTime);
	void render(CTable* gTable, std::map<std::string, GameObject*> gm);
	~Teleporter();

	std::vector<CLineSegment> _lines;
	std::vector<int> _lineIndex;
private:
	TransformComponent * t;
	RigidBodyComponent* r;
};
#endif 