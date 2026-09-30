#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObject.h"
#include "table.h"

//@desc Rigid Body Component to hold physics variables and to help for future expansions
//--------------------------------------------------------------------------------------------------
class RigidBodyComponent : public GameComponent {
public:
	bool bIsFirstTimeLuanch = true;
	bool _bGravityEnable = false;

	CPoint _acceleration;
	CPoint _velocity;
	float _angularAcceleration;
	float _angularVelocity;
	float _gravity = -0.000098f;;
};
#endif 
