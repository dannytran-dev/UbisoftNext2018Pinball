#ifndef SPINNER_H
#define SPINNER_H

#include "GameObject.h"
#include "table.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsComponent.h"

//@desc Spinners gameobject to help the line spin in a circle.
//--------------------------------------------------------------------------------------------------
class Spinner : public GameObject
{
public:
	Spinner(float x, float y);
	void update(float deltaTime);
	void render(CTable* gTable, std::map<std::string, GameObject*> gm);
	void Constraints();
	~Spinner();

	std::vector<CLineSegment> _lines;
	std::vector<int> _lineIndex;
private:
	TransformComponent * t;
	RigidBodyComponent* r;
	PhysicsComponent* p;
};
#endif 