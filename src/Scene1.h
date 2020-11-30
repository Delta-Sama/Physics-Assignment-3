#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Background.h"
#include "Bullet.h"
#include "Button.h"
#include "Scene.h"
#include "ObjectPoolManager.h"
#include "ObjectPoolManager.cpp"
#include "ship.h"

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	ObjectPool<Bullet>* m_pool;
	Ship* m_ship;
	int m_add_cooldown;

	Button* m_pNextButton;
	Button* m_pMenuButton;
	Background* m_pbackground;
	
};

#endif /* defined (__PLAY_SCENE__) */