#pragma once
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "Sprite.h"

class Background : public Sprite
{
public:
	Background();
	~Background();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
};

#endif