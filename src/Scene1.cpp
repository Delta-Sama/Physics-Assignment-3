#include "Scene1.h"

#include "Game.h"
#include "EventManager.h"

Scene1::Scene1()
{
	Scene1::start();
}

Scene1::~Scene1()
= default;

// SCENE

bool BulletTest(Bullet* a)
{
	if (a->getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}

void Scene1::start()
{
	m_pool = new ObjectPool<Bullet> (Config::NUMBER_OF_BULLETS, BulletTest);

	m_ship = new Ship;
	addChild(m_ship);
	m_ship->getTransform()->position = EventManager::Instance().getMousePosition();

	SoundManager::Instance().setSoundVolume(5);
	SoundManager::Instance().load("../Assets/audio/yay.ogg", "explosion", SoundType::SOUND_SFX);
}

void Scene1::update()
{
	updateDisplayList();

	m_pool->Update();
	
	if (m_add_cooldown-- <= 0)
	{
		m_add_cooldown = Config::FPS * 0.2;

		Bullet* bullet = m_pool->GetFreeObject();
		if (bullet != nullptr)
		{
			bullet->getRigidBody()->velocity = glm::vec2(0,0);
			bullet->getTransform()->position = glm::vec2(rand() % Config::SCREEN_WIDTH,0);
		}
	}

	for (int i = 0; i < m_pool->GetSize(); i++)
	{
		PoolObject<Bullet>* obj = &(m_pool->GetObjectsPool()[i]);
		if (obj->inUse && !obj->used)
		{
			if (CollisionManager::AABBCheck(obj->object,m_ship))
			{
				obj->used = true;
				SoundManager::Instance().playSound("explosion", 0);
			}
		}
	}
}

void Scene1::handleEvents()
{
	EventManager::Instance().update();

	//if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))

	//if (EventManager::Instance().getMouseButton(0))

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void Scene1::draw()
{
	drawDisplayList();

	m_pool->Draw();
}

void Scene1::clean()
{
	removeAllChildren();

	m_pool->Clean();
	delete m_pool;
}