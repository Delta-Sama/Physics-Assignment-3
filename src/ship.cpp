#include "ship.h"

#include <algorithm>

#include "CollisionManager.h"
#include "EventManager.h"
#include "MathManager.h"
#include "glm/gtx/string_cast.hpp"
#include "Scene1.h"
#include "TextureManager.h"
#include "Util.h"

const float MIN_MOVE_DIST = 10.0f;
const float MOVE_SPEED = 2.0f;
const float TURN_SPEED = 4.0f;

Ship::Ship()
{
	TextureManager::Instance()->load("../Assets/textures/ship.png","ship");

	auto size = TextureManager::Instance()->getTextureSize("ship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
	
	m_currentHeading = 0.0f; // current facing angle
	m_currentDirection = glm::vec2(1.0f, 0.0f); // facing right
}


Ship::~Ship()
= default;

void Ship::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TextureManager::Instance()->draw("ship", x, y, m_currentHeading, 255, true, SDL_FLIP_NONE, {getWidth(),getHeight()});
}


void Ship::update()
{
	const float sq_dist = CollisionManager::squaredDistance(EventManager::Instance().getMousePosition(), getTransform()->position);

	const float dif_x = EventManager::Instance().getMousePosition().x - getTransform()->position.x;
	const float dif_y = EventManager::Instance().getMousePosition().y - getTransform()->position.y;
	
	if (sq_dist > MIN_MOVE_DIST * MIN_MOVE_DIST)
	{
		const float angle = atan2(dif_y, dif_x);
		const float x = cos(angle) * MOVE_SPEED * Config::METERS_TO_PIXELS;
		const float y = sin(angle) * MOVE_SPEED * Config::METERS_TO_PIXELS;

		m_currentHeading = MAMA::To180Deg(MAMA::RadToDeg(angle)) + 90.0f;
		
		getTransform()->position += glm::vec2(x,y);
	}
}

void Ship::clean()
{
}
