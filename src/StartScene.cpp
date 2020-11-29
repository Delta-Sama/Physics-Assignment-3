#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();

	if (cur_frame > 0)
	{
		cur_frame--;
		m_pStartButton->getTransform()->rotation.x += 3.0f;
		m_pStartButton->getTransform()->position.x -= 1.0f;
		m_pStartButton->getTransform()->position.y += 14.0f;
	}
	else if (cur_frame == 0) {
		TheGame::Instance()->changeSceneState(PLAY2_SCENE);
	}
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY1_SCENE);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(PLAY2_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pNameLabel = new Label("DOBRIVSKIY MAXIM", "Dock51", 80, blue, glm::vec2(Config::SCREEN_WIDTH/2, 40.0f));
	m_pNameLabel->setParent(this);
	addChild(m_pNameLabel);

	m_pStudentNumLabel = new Label("101290100", "Dock51", 40, { 0, 0, 150, 255 }, glm::vec2(Config::SCREEN_WIDTH / 2, 120.0f));
	m_pStudentNumLabel->setParent(this);
	addChild(m_pStudentNumLabel);

	// Start Button
	m_pStartButton = new Button();// "../Assets/textures/PlayB.png");
	m_pStartButton->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH / 2, 400.0f);
	m_pStartButton->getTransform()->rotation = glm::vec2(0.0f, 0.0f);
	
	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		cur_frame = max_frame;
		m_pStartButton->setActive(false);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		if (m_pStartButton->getActive())
		{
			m_pStartButton->getTransform()->rotation.x = 5.0f;
			m_pStartButton->getTransform()->position.y = 405.0f;
			m_pStartButton->setAlpha(200);
		}
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		if (m_pStartButton->getActive())
		{
			m_pStartButton->getTransform()->rotation.x = 0.0f;
			m_pStartButton->getTransform()->position.y = 400.0f;
			m_pStartButton->setAlpha(255);
		}
	});
	addChild(m_pStartButton);

	
}

