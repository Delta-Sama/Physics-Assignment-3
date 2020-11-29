#include "WayPoint.h"
#include "TextureManager.h"

WayPoint::WayPoint()
{
	TextureManager::Instance()->load("../Assets/textures/Circle.png","waypoint");

	setWidth(5);
	setHeight(5);

	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);
}

WayPoint::~WayPoint()
= default;

void WayPoint::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	
	TextureManager::Instance()->draw("waypoint", x, y, 0, 255, true, SDL_FLIP_NONE, { getWidth(),getHeight() });
}

void WayPoint::update()
{
	
}

void WayPoint::clean()
{
	
}