#include "Scene2.h"

#include "Game.h"
#include "EventManager.h"
#include "MathManager.h"
#include "PhysicsManager.h"
#include "Util.h"

Scene2::Scene2()
{
	Scene2::start();
}

Scene2::~Scene2()
= default;

// SCENE

void Scene2::start()
{
	m_crate = new Crate(glm::vec2(500.0f, 500.0f), glm::vec2(60.0f, 60.0f));
	addChild(m_crate);
	PhysicsManager::AddPhysicalObject(*m_crate);

	m_ball = new BouncingBall(glm::vec2(300.0f, 100.0f));
	m_ball->getRigidBody()->velocity = {4.0f,2.0f};
	addChild(m_ball);
	PhysicsManager::AddPhysicalObject(*m_ball);
}

void Scene2::update()
{
	updateDisplayList();
	//Util::QueueLine(m_crate->getTransform()->position, m_ball->getTransform()->position, { 1,0,0,1 });
}

void Scene2::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_ball->getRigidBody()->velocity.y -= 0.5f;
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_ball->getRigidBody()->velocity.x -= 0.2f;
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_ball->getRigidBody()->velocity.x += 0.2f;
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		m_ball->getRigidBody()->velocity.y += 0.5f;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_R))
	{
		m_ball->getRigidBody()->velocity = { 0.0f,0.0f };
		m_crate->getRigidBody()->velocity = { 0.0f,0.0f };
		if (EventManager::Instance().KeyPressed(SDL_SCANCODE_A))
		{
			m_ball->getTransform()->position = { 350.0f, 350.0f };
			m_crate->getTransform()->position = { 550.0f, 350.0f };
		}
		else if (EventManager::Instance().KeyPressed(SDL_SCANCODE_D))
		{
			m_ball->getTransform()->position = { 550.0f, 350.0f };
			m_crate->getTransform()->position = { 350.0f, 350.0f };
		}
		else if (EventManager::Instance().KeyPressed(SDL_SCANCODE_S))
		{
			m_ball->getTransform()->position = { 450.0f, 100.0f };
			m_crate->getTransform()->position = { 450.0f, 450.0f };
		}
		else if (EventManager::Instance().KeyPressed(SDL_SCANCODE_W))
		{
			m_ball->getTransform()->position = { 450.0f, 450.0f };
			m_crate->getTransform()->position = { 450.0f, 100.0f };
		}
	}

	if (EventManager::Instance().KeyPressed(SDL_SCANCODE_SPACE))
	{
		if (Config::FPS == 60.0f)
			Config::FPS = 2.0f;
		else
			Config::FPS = 60.0f;
	}

	//if (EventManager::Instance().getMouseButton(0))

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void Scene2::draw()
{
	drawDisplayList();
	Util::DrawQueue();
}

void Scene2::clean()
{
	removeAllChildren();
}