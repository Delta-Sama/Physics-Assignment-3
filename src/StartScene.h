#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "ship.h"
#include "Button.h"

class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	
private:
	Label* m_pNameLabel{};
	Label* m_pStudentNumLabel{};

	Ship* m_pShip{};

	Button* m_pStartButton;

	int cur_frame = -1;
	int max_frame = 20;
};

#endif /* defined (__START_SCENE__) */