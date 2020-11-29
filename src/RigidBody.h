#pragma once
#ifndef __RIGID_BODY__
#define __RIGID_BODY__
#include <glm/vec2.hpp>


enum CollisionShape { RECTANGLE, CIRCLE, TRIANGLE };

struct RigidBody
{
	float mass;
	float inverse_mass;
	float elasticity;

	CollisionShape shape;
	
	glm::vec2 velocity;
	glm::vec2 acceleration;
	glm::vec2 direction;
	glm::vec2 force;
	
	bool isColliding;
	bool anchored;
	bool moved;

	void SetMass(float m)
	{
		mass = m;
		inverse_mass = (mass != 0.0f ? (1 / mass) : 0);
	}
	
	glm::vec2 GetMomentum()
	{
		return glm::vec2(mass * velocity.x, mass * velocity.y);
	}
};

#endif /* defined (__RIGID_BODY__) */