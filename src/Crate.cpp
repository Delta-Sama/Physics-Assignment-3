#include "Crate.h"

#include "CollisionManager.h"
#include "EventManager.h"
#include "TextureManager.h"

Crate::Crate(glm::vec2 pos, glm::vec2 size)
{
	TextureManager::Instance()->load("../Assets/textures/Crate.png", "crate");

	setWidth(size.x);
	setHeight(size.y);

	getRigidBody()->elasticity = 0.15f;
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	getRigidBody()->SetMass(3.0f);
	
	setShape(CollisionShape::RECTANGLE);
	setType(BRICK);

	getTransform()->position = pos;
	getRigidBody()->velocity = glm::vec2(5.0f, 2.0f);
}

Crate::~Crate() = default;

void Crate::update()
{
	getRigidBody()->velocity.y += -Config::g / 60.0f;
	//getRigidBody()->velocity = { 0,0 };
	
	if (EventManager::Instance().getMouseButton(0))
	{
		glm::vec2 m = EventManager::Instance().getMousePosition();
		glm::vec2 direction = m - getTransform()->position;
		float len = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction = { direction.x / len, direction.y / len };
		
		getRigidBody()->velocity += direction * 0.4f;
	}
	
	ADCOMA::SweptAABB(this);
}

void Crate::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	const float ang = getTransform()->rotation.x;

	TextureManager::Instance()->draw("crate", x, y, ang, 255, true, SDL_FLIP_NONE, { getWidth(),getHeight() });
}

void Crate::clean()
{
	
}