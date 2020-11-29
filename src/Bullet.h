#pragma once
#ifndef __GRANADE_H__
#define __GRANADE_H__

#include "Sprite.h"

class Bullet final : public Sprite
{
public:
	Bullet();
	~Bullet();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

};

#endif /* defined (__PLANE__) */
