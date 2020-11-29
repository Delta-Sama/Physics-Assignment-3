#include "Scene2.h"

#include "Game.h"
#include "EventManager.h"
#include "imgui.h"
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
	m_background = new Background();
	addChild(m_background);
	
	m_crate = new Crate(glm::vec2(500.0f, 500.0f), glm::vec2(70.0f, 70.0f));
	addChild(m_crate);
	PhysicsManager::AddPhysicalObject(*m_crate);

	m_ball = new BouncingBall(glm::vec2(300.0f, 500.0f));
	addChild(m_ball);
	PhysicsManager::AddPhysicalObject(*m_ball);
}

void Scene2::update()
{
	updateDisplayList();
	
	Util::QueueLine(m_crate->getTransform()->position, m_ball->getTransform()->position, { 1,0,0,1 });
	
	ImGui::SetNextWindowSize(ImVec2(300.0f,250.0f));
	ImGui::Begin("Physics panel");
	ImGui::Text("Crate settings");
	ImGui::SliderFloat("kg Crate", &m_crate->getRigidBody()->mass, 1.0f, 100.0f);
	ImGui::SliderFloat(" elasticity", &m_crate->getRigidBody()->elasticity, 0.0f, 1.0f);
	ImGui::Text("Object settings");
	ImGui::SliderFloat("kg Object", &m_ball->getRigidBody()->mass, 1.0f, 100.0f);
	ImGui::SliderFloat(" elasticity ", &m_ball->getRigidBody()->elasticity, 0.0f, 1.0f);
	if (ImGui::Button("Shape: CIRCLE"))
	{
		m_ball->setShape(CollisionShape::CIRCLE);
	}
	if (ImGui::Button("Shape: RECTANGLE"))
	{
		m_ball->setShape(CollisionShape::RECTANGLE);
	}
	ImGui::Text("World settings");
	ImGui::SliderFloat(" gravity", &Config::g, -100.0f, 0.0f);
	ImGui::Checkbox("Low FPS", &lowFPS);
	ImGui::Checkbox("Debug mode", &Util::debugMode);
	Config::FPS = lowFPS == true ? 2.0f : 60.0f;
	if (ImGui::Button("Reset Scene"))
	{
		m_crate->getRigidBody()->velocity = { 0.0f,0.0f };
		m_ball->getRigidBody()->velocity = { 0.0f,0.0f };
		m_crate->getTransform()->position = { 500.0f,500.0f };
		m_ball->getTransform()->position = { 300.0f,500.0f };

		Config::g = -9.8f;
		m_ball->setShape(CollisionShape::CIRCLE);
		m_crate->getRigidBody()->mass = 3.0f;
		m_ball->getRigidBody()->mass = 1.0f;
		m_crate->getRigidBody()->elasticity = 0.15f;
		m_ball->getRigidBody()->elasticity = 0.85f;
	}
	
	ImGui::End();
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