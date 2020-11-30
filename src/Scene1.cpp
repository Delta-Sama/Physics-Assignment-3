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

	m_pbackground = new Background("../Assets/textures/CosmoBackground.jpg");
	addChild(m_pbackground);
	
	m_ship = new Ship;
	m_ship->setWidth(50.0f);
	m_ship->setHeight(50.0f);
	addChild(m_ship);
	m_ship->getTransform()->position = EventManager::Instance().getMousePosition();
	
	SoundManager::Instance().setSoundVolume(5);
	SoundManager::Instance().load("../Assets/audio/yay.ogg", "explosion", SoundType::SOUND_SFX);

	m_pNextButton = new Button("../Assets/textures/nextButton.png","NextB");
	m_pNextButton->setWidth(110.0f);
	m_pNextButton->setHeight(40.0f);
	m_pNextButton->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - 70.0f, Config::SCREEN_HEIGHT - 40.0f);
	addChild(m_pNextButton);

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pNextButton->setAlpha(220);
			m_pNextButton->getTransform()->rotation.x = -10.0f;
		});
	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pNextButton->setAlpha(255);
			m_pNextButton->getTransform()->rotation.x = 0.0f;
		});
	m_pNextButton->addEventListener(CLICK, [&]()-> void
		{
			TheGame::Instance()->changeSceneState(PLAY2_SCENE);
		});

	m_pMenuButton = new Button("../Assets/textures/menuButton.png","MenuB");
	m_pMenuButton->setWidth(110.0f);
	m_pMenuButton->setHeight(40.0f);
	m_pMenuButton->getTransform()->position = glm::vec2(70.0f, Config::SCREEN_HEIGHT - 40.0f);
	addChild(m_pMenuButton);

	m_pMenuButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pMenuButton->setAlpha(220);
			m_pMenuButton->getTransform()->rotation.x = 10.0f;
		});
	m_pMenuButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pMenuButton->setAlpha(255);
			m_pMenuButton->getTransform()->rotation.x = 0.0f;
		});
	m_pMenuButton->addEventListener(CLICK, [&]()-> void
		{
			TheGame::Instance()->changeSceneState(START_SCENE);
		});
}

void Scene1::update()
{
	if (!active) return;
	
	updateDisplayList();
	
	if (!active) return;
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
	if (!active) return;
	
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
	if (!active) return;
	
	drawDisplayList();

	m_pool->Draw();
}

void Scene1::clean()
{
	removeAllChildren();

	m_pool->Clean();
	delete m_pool;
}