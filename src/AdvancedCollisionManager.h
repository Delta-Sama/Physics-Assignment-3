#pragma once
#ifndef __ADV_COLLISION_MANAGER__
#define __ADV_COLLISION_MANAGER__

#include "GameObject.h"
#include "ship.h"
#include <GLM/gtx/norm.hpp>

#include "PhysicsManager.h"

class AdvancedCollisionManager
{
public:
	static struct Manifold SweptAABB(GameObject* obj1, GameObject* obj2);
	static struct Manifold SweptAABB(GameObject* obj);
	
private:
	static struct Manifold SweptRectRect(GameObject* obj1, GameObject* obj2);
	static struct Manifold SweptCircleRect(GameObject* obj1, GameObject* obj2);
	//static float SweptCircleCircle(GameObject* obj1, GameObject* obj2, glm::vec2& normal);
	
	AdvancedCollisionManager();
	~AdvancedCollisionManager();
};

typedef AdvancedCollisionManager ADCOMA;

#endif