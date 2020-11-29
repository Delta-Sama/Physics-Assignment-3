#include "Player.h"

#include <algorithm>

#include "TextureManager.h"
#include "Config.h"

const int X_SIZE = 15;
const int Y_SIZE = 20;

Player::Player()
{
	TextureManager::Instance()->load("../Assets/textures/wookie.png", "wookie");

	setWidth(X_SIZE);
	setHeight(Y_SIZE);
	
	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->direction = glm::vec2(0.0f, 0.0f);
	getRigidBody()->force = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	const auto ang = getTransform()->rotation.x;
	
	TextureManager::Instance()->draw("wookie", x, y, ang, 255, true, SDL_FLIP_NONE, { getWidth(),getHeight() });
}

void Player::update()
{
	const float deltaTime = 1.0f / 60.f;

	
}

void Player::clean()
{

}

std::string Player::checkDistance(GameObject * pGameObject) {
	return "";
}
