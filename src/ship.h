#pragma once
#ifndef __SHIP__
#define __SHIP__

#include "DisplayObject.h"
#include "TextureManager.h"

class Ship final : public DisplayObject
{
public:
	Ship();
	~Ship();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

private:
	
	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;
};


#endif /* defined (__SHIP__) */

