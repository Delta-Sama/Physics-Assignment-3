#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "Sprite.h"
#include "Label.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	std::string checkDistance(GameObject* pGameObject);

private:
	
};

#endif /* defined (__PLAYER__) */