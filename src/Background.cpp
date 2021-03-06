#include "Background.h"
#include "TextureManager.h"

const int X_SIZE = Config::SCREEN_WIDTH;
const int Y_SIZE = Config::SCREEN_HEIGHT;

Background::Background(const std::string& image_path) {
	TextureManager::Instance()->load(image_path, image_path);
	key = image_path;
	
	setWidth(X_SIZE);
	setHeight(Y_SIZE);

	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BACKGROUND);
}

Background::~Background()
= default;

void Background::draw() {
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	const auto ang = getTransform()->rotation.x;

	TextureManager::Instance()->draw(key, x, y, ang, 255, false, SDL_FLIP_NONE, { getWidth(),getHeight() });
}

void Background::update() {

}

void Background::clean() {

}