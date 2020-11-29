#pragma once
#ifndef __CRATE_H__
#define __CRATE_H__

#include "Sprite.h"

class Crate final : public Sprite
{
public:
	Crate(glm::vec2 pos, glm::vec2 size = glm::vec2(40,40));
	~Crate();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void CollisionResponse(float collision_time, glm::vec2 normal);

private:

};

#endif
