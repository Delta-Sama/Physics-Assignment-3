#include "Enemy.h"
#include "TextureManager.h"

const int X_SIZE = 25;
const int Y_SIZE = 25;

Enemy::Enemy() {
	TextureManager::Instance()->load("../Assets/textures/stormtrooper.png", "stormtrooper");

	setWidth(X_SIZE);
	setHeight(Y_SIZE);

	getTransform()->position = glm::vec2(700.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(ENEMY);
}

Enemy::~Enemy()
= default;

void Enemy::draw() {
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	const auto ang = getTransform()->rotation.x;

	TextureManager::Instance()->draw("stormtrooper", x, y, ang, 255, true, SDL_FLIP_NONE, { getWidth(),getHeight() });
}

void Enemy::update() {

}

void Enemy::clean() {

}