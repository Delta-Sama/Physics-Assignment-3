#include "BouncingBall.h"

#include <algorithm>

#include "CollisionManager.h"
#include "Config.h"
#include "PhysicsManager.h"

BouncingBall::BouncingBall(glm::vec2 pos)
{
	TextureManager::Instance()->load("../Assets/textures/BasketballBall.png", "ball");
	TextureManager::Instance()->load("../Assets/textures/BasketballBox.png", "box");
	TextureManager::Instance()->load("../Assets/textures/BasketballBallShadow.png", "ball_shadow");
	TextureManager::Instance()->load("../Assets/textures/BasketballBoxShadow.png", "box_shadow");
	
	setWidth(40);
	setHeight(40);

	getRigidBody()->elasticity = 0.85f;
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	getRigidBody()->SetMass(1.0f);
	
	setType(BOUNCING_OBJECT);
	setShape(CollisionShape::CIRCLE);

	getTransform()->position = pos;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
}

BouncingBall::~BouncingBall() = default;

void BouncingBall::update()
{
	switch (getShape())
	{
	case RECTANGLE:
		getTransform()->rotation.x = 0;
		break;
	case CIRCLE:
		getTransform()->rotation.x += std::clamp(getRigidBody()->velocity.x,
			-Config::MAX_ROTATION, Config::MAX_ROTATION);
		break;
	default:
		break;
	}

	getRigidBody()->velocity.y += -Config::g / 60.0f;

	// Swept collision
	ADCOMA::SweptAABB(this);
	PhysicsManager::CheckWorldCollision(*this);
	
}

void BouncingBall::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	const float ang = getTransform()->rotation.x;

	float shadow_w = getWidth() * (getTransform()->position.y / Config::BOTTOM_BORDER);
	
	std::string id;
	std::string shadow_id;
	switch (getShape())
	{
	case RECTANGLE:
		id = "box";
		shadow_id = "box_shadow";
		break;
	case CIRCLE:
		id = "ball";
		shadow_id = "ball_shadow";
		break;
	default:
		break;
	}

	TextureManager::Instance()->draw(shadow_id, x, Config::BOTTOM_BORDER - getHeight() / 2, 0, 255, true,
		SDL_FLIP_NONE, { shadow_w,getHeight() });
	TextureManager::Instance()->draw(id, x, y, ang, 255, true, SDL_FLIP_NONE, { getWidth(),getHeight() });
}

void BouncingBall::clean()
{
	
}