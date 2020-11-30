#pragma once
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "Sprite.h"

class Background : public Sprite
{
public:
	Background(const std::string& image_path = "../Assets/textures/Background.jpg");
	~Background();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	std::string key;
};

#endif