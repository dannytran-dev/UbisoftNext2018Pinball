#ifndef FLIPPERSRIGHT_H
#define FLIPPERSRIGHT_H

#include "GameObject.h"
#include "table.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsComponent.h"

//@desc Right flipper gameobject.
//--------------------------------------------------------------------------------------------------
class FlippersRight : public GameObject
{
public:
	FlippersRight(float x, float y);
	~FlippersRight();
	void update(float deltaTime);
	void render(CTable* gTable, std::map<std::string, GameObject*> gm);
	void FlippersRight::Constraints();

	std::vector<CLineSegment> _lines;
	std::vector<int> _lineIndex;
private:
	TransformComponent * t;
	RigidBodyComponent* r;
	PhysicsComponent* p;
};
#endif 