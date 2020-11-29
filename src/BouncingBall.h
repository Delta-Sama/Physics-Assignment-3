#pragma once
#ifndef __BALL_H__
#define __BALL_H__

#include "Sprite.h"

class BouncingBall final : public Sprite
{
public:
	BouncingBall(glm::vec2 pos);
	~BouncingBall();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void CollisionResponse(float collision_time, glm::vec2 normal);

private:
	
};

#endif /* defined (__PLANE__) */
