#pragma once
#ifndef __PHYSICS_MANAGER__
#define __PHYSICS_MANAGER__

// core libraries
#include <iostream>

#include "GameObject.h"
#include "ship.h"
#include <GLM/gtx/norm.hpp>
#include "SoundManager.h"
#include "AdvancedCollisionManager.h"

struct Manifold
{
	bool result;
	GameObject* A;
	GameObject* B;
	glm::vec2 normal;
	float collisionTime;
};

class PhysicsManager
{
public:
	static void AddPhysicalObject(GameObject& obj);
	
	static float CheckWorldCollision(GameObject& obj);
	
	static std::list<GameObject*>* GetPhysicalObjects() { return &m_physical_objects; }

private:
	PhysicsManager();
	~PhysicsManager();

private:
	static std::list<GameObject*> m_physical_objects;
	
};

#endif /* defined (__COLLISION_MANAGER__) */