#pragma once
#ifndef __PLAY_SCENE_2__
#define __PLAY_SCENE_2__

#include "BouncingBall.h"
#include "Bullet.h"
#include "Crate.h"
#include "Scene.h"
#include "ship.h"

class Scene2 : public Scene
{
public:
	Scene2();
	~Scene2();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	BouncingBall* m_ball;
	Crate* m_crate;

};

#endif /* defined (__PLAY_SCENE__) */