#ifndef PHYSICS_H
#define PHYSICS_H
#include <algorithm>

#include "GameObject.h"
#include "GameObjectManager.h"
#include "table.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

//@desc Physics Component to calcuate and apply physics to gameobjects and to help for future expansions
//--------------------------------------------------------------------------------------------------
class PhysicsComponent : public GameComponent {
public:
	int radius;
	float score = 0.0f;
	bool bIsCollision = false;
	CPoint _normal;

	bool CollisionCheck(CTable* gTable, std::map<std::string, GameObject*> gm);
	void CollisionResolve(GameObject* a, float attenuation);
	void ApplyTorque(float a);

protected:
private:
};
#endif 