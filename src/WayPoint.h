#pragma once
#ifndef __WAYPOINT_H__
#define __WAYPOINT_H__

#include "Sprite.h"

class WayPoint final : public Sprite
{
public:
	WayPoint();
	~WayPoint();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	
};

#endif /* defined (__PLANE__) */
