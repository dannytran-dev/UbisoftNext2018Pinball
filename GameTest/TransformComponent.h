#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "GameObject.h"
#include "table.h"

//@desc Transform Component to basic positional varaibles and to help for future expansions
//--------------------------------------------------------------------------------------------------
class TransformComponent : public GameComponent {
public:
	CPoint _position;
	float _rotation;
};
#endif 
