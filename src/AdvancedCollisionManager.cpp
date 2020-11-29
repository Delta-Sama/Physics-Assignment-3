#include "AdvancedCollisionManager.h"

#include <algorithm>

#include "MathManager.h"
#include "PhysicsManager.h"
#include "Util.h"

AdvancedCollisionManager::AdvancedCollisionManager()
{
}

AdvancedCollisionManager::~AdvancedCollisionManager() = default;

Manifold AdvancedCollisionManager::SweptAABB(GameObject* obj)
{
	Manifold result;
	
	float xEntryDist, yEntryDist;
	float xExitDist, yExitDist;

	const float l = std::numeric_limits<float>::infinity();
	
	const glm::vec2 vel1 = obj->getRigidBody()->velocity;
	const glm::vec2 pos1 = obj->getTransform()->position;
	const glm::vec2 size1 = glm::vec2(obj->getWidth(), obj->getHeight());

	// Distance between the object and the nearest edge
	if (vel1.x > 0.0f) {
		xEntryDist = Config::SCREEN_WIDTH - (pos1.x + size1.x / 2);
		xExitDist = Config::SCREEN_WIDTH + l - (pos1.x + size1.x / 2);
	}
	else {
		xEntryDist = 0 - (pos1.x - size1.x / 2);
		xExitDist = -l - (pos1.x - size1.x / 2);
	}

	if (vel1.y > 0.0f) {
		yEntryDist = Config::BOTTOM_BORDER - (pos1.y + size1.y / 2);
		yExitDist = (Config::BOTTOM_BORDER + l) - (pos1.y + size1.y / 2);
	}
	else {
		yEntryDist = 0 - (pos1.y - size1.y / 2);
		yExitDist = -l - (pos1.y - size1.y / 2);
	}

	float xEntryTime, yEntryTime;

	// Time to reach the closest edge
	if (vel1.x == 0.0f) {
		xEntryTime = std::numeric_limits<float>::infinity();
	}
	else {
		xEntryTime = xEntryDist / vel1.x;
	}

	if (vel1.y == 0.0f) {
		yEntryTime = std::numeric_limits<float>::infinity();
	}
	else {
		yEntryTime = yEntryDist / vel1.y;
	}

	const float entryTime = std::min(xEntryTime, yEntryTime);

	// No collision case
	if (xEntryTime < 0.0f && yEntryTime < 0.0f || xEntryTime > 1.0f && yEntryTime > 1.0f)
	{
		result.normal.x = 0.0f;
		result.normal.y = 0.0f;
		result.collisionTime = 1.0f;

		obj->getTransform()->position.x += obj->getRigidBody()->velocity.x;
		obj->getTransform()->position.y += obj->getRigidBody()->velocity.y;
		
		return result;
	}
	
	// Collision was found
	result.normal.x = 0.0f;
	result.normal.y = 0.0f;

	if (xEntryTime < yEntryTime)
		(xEntryDist > 0.0f) ? result.normal.x = -1.0f : result.normal.x = 1.0f;
	else
		(yEntryDist > 0.0f) ? result.normal.y = -1.0f : result.normal.y = 1.0f;

	result.collisionTime = entryTime;

	if (result.collisionTime < 1.0f)
	{
		if (abs(result.normal.y) == 0)
			obj->getRigidBody()->velocity.x *= obj->getRigidBody()->elasticity;
		else
			obj->getRigidBody()->velocity.x *= 0.99f;
		
		obj->getRigidBody()->velocity.y *= obj->getRigidBody()->elasticity;
	}

	if (abs(result.normal.y) == 0)
		obj->getTransform()->position.x += obj->getRigidBody()->velocity.x * result.collisionTime;
	else
		obj->getTransform()->position.x += obj->getRigidBody()->velocity.x;
	
	obj->getTransform()->position.y += obj->getRigidBody()->velocity.y * result.collisionTime;

	if (abs(result.normal.x) > 0.0001f)
	{
		obj->getRigidBody()->velocity.x = -obj->getRigidBody()->velocity.x;
	}
	if (abs(result.normal.y) > 0.0001f)
	{
		obj->getRigidBody()->velocity.y = -obj->getRigidBody()->velocity.y;
	}

	/*const int k = 2;
	if (obj->getTransform()->position.x - obj->getWidth() / 2 - k < 0)
		obj->getTransform()->position.x = obj->getWidth() / 2 + 1;
	if (obj->getTransform()->position.x + obj->getWidth() / 2 + k > Config::SCREEN_WIDTH)
		obj->getTransform()->position.x = Config::SCREEN_WIDTH - obj->getWidth() / 2 - 1;
	if (obj->getTransform()->position.y - obj->getHeight() / 2 - k < 0)
		obj->getTransform()->position.y = obj->getHeight() / 2 + 1;
	if (obj->getTransform()->position.y + obj->getHeight() / 2 + k > Config::BOTTOM_BORDER)
		obj->getTransform()->position.y = Config::BOTTOM_BORDER - obj->getHeight() / 2 - 1;*/
	
	return result;
}

Manifold AdvancedCollisionManager::SweptAABB(GameObject* obj1, GameObject* obj2)
{
	Manifold result;
	
	if (obj1->getShape() == CollisionShape::CIRCLE && obj2->getShape() == CollisionShape::RECTANGLE) // Circle-Rect
		result = AdvancedCollisionManager::SweptCircleRect(obj1, obj2);
	else if (obj1->getShape() == CollisionShape::RECTANGLE && obj2->getShape() == CollisionShape::CIRCLE) // Rect-Circle
		result = AdvancedCollisionManager::SweptCircleRect(obj2, obj1);
	else
		result = AdvancedCollisionManager::SweptRectRect(obj1, obj2);

	return result;
}

Manifold AdvancedCollisionManager::SweptRectRect(GameObject* obj1, GameObject* obj2)
{
	Manifold result;
	result.A = obj1;
	result.B = obj2;

	const glm::vec2 vel1 = obj1->getRigidBody()->velocity;
	const glm::vec2 vel2 = obj1->getRigidBody()->velocity;

	glm::vec2 pos1 = obj1->getTransform()->position;
	glm::vec2 pos2 = obj2->getTransform()->position;

	const glm::vec2 movedPos1 = pos1 + vel1;
	const glm::vec2 movedPos2 = pos2 + vel2;

	const glm::vec2 size1 = glm::vec2(obj1->getWidth(), obj1->getHeight());
	const glm::vec2 size2 = glm::vec2(obj2->getWidth(), obj2->getHeight());

	float testX = movedPos1.x;
	float testY = movedPos1.y;

	if (pos1.x < pos2.x - size2.x / 2) testX = pos2.x - size2.x / 2; // left edge
	else if (pos1.x > pos2.x + size2.x / 2) testX = pos2.x + size2.x / 2; // right edge

	if (pos1.y < pos2.y - size2.y / 2) testY = pos2.y - size2.y / 2; // top edge
	else if (pos1.y > pos2.y + size2.y / 2) testY = pos2.y + size2.y / 2; // bottom edge

	const float distX = testX - pos1.x;
	const float distY = testY - pos1.y;

	// If no collision
	if (!(movedPos1.x - size1.x / 2 < movedPos2.x + size2.x / 2 &&
		movedPos1.x + size1.x / 2 > movedPos2.x - size2.x / 2 &&
		movedPos1.y - size1.y / 2 < movedPos2.y + size2.y / 2 &&
		movedPos1.y + size1.y / 2 > movedPos2.y - size2.y / 2))
	{
		result.normal.x = 0.0f;
		result.normal.y = 0.0f;
		result.result = false;
		result.collisionTime = 1.0f;
		return result;
	}

	result.result = true;

	float difX = size1.x / 2 + size2.x / 2 - abs(movedPos2.x - movedPos1.x);
	float difY = size1.y / 2 + size2.y / 2 - abs(movedPos2.y - movedPos1.y);

	glm::vec2 diffMove1;
	glm::vec2 diffMove2;
	
	// Determine the normal
	if (abs(distX) > abs(distY))
	{
		result.normal.x = (distX > 0.0f ? -1.0f : 1.0f);
		result.normal.y = 0.0f;

		float velsum = abs(obj1->getRigidBody()->velocity.x) + abs(obj2->getRigidBody()->velocity.x);
		float propK1 = abs(obj1->getRigidBody()->velocity.x) / velsum;
		float propK2 = abs(obj2->getRigidBody()->velocity.x) / velsum;
		
		diffMove1 = { -result.normal.x * (difX + abs(vel1.x) + 0.0f) * propK1, 0.0f };
		diffMove2 = { result.normal.x * (difX + abs(vel2.x) + 0.0f) * propK2, 0.0f };
	}
	else
	{
		result.normal.x = 0.0f;
		result.normal.y = (distY > 0.0f ? -1.0f : 1.0f);

		float velsum = abs(obj1->getRigidBody()->velocity.y) + abs(obj2->getRigidBody()->velocity.y);
		float propK1 = abs(obj1->getRigidBody()->velocity.y) / velsum;
		float propK2 = abs(obj2->getRigidBody()->velocity.y) / velsum;

		diffMove1 = { 0.0f, -result.normal.y * (difY + abs(vel1.y) + 0.0f) * propK1 };
		diffMove2 = { 0.0f, result.normal.y * (difY + abs(vel2.y) + 0.0f) * propK2 };
	}

	obj1->getTransform()->position += obj1->getRigidBody()->velocity - diffMove1;
	obj2->getTransform()->position += obj2->getRigidBody()->velocity - diffMove2;

	return result;
}

Manifold AdvancedCollisionManager::SweptCircleRect(GameObject* obj1, GameObject* obj2)
{
	Manifold result;
	result.A = obj1;
	result.B = obj2;
	
	const glm::vec2 vel1 = obj1->getRigidBody()->velocity;
	const glm::vec2 vel2 = obj1->getRigidBody()->velocity;

	glm::vec2 pos1 = obj1->getTransform()->position;
	glm::vec2 pos2 = obj2->getTransform()->position;

	const glm::vec2 movedPos1 = pos1 + vel1;
	const glm::vec2 movedPos2 = pos2 + vel2;

	const glm::vec2 size1 = glm::vec2(obj1->getWidth(), obj1->getHeight());
	const glm::vec2 size2 = glm::vec2(obj2->getWidth(), obj2->getHeight());

	const float radius = size1.x / 2;
	
	float testX = movedPos1.x;
	float testY = movedPos1.y;

	if (pos1.x < pos2.x - size2.x / 2) testX = pos2.x - size2.x / 2; // left edge
	else if (pos1.x > pos2.x + size2.x / 2) testX = pos2.x + size2.x / 2; // right edge

	if (pos1.y < pos2.y - size2.y / 2) testY = pos2.y - size2.y / 2; // top edge
	else if (pos1.y > pos2.y + size2.y / 2) testY = pos2.y + size2.y / 2; // bottom edge

	const float distX = testX - pos1.x;
	const float distY = testY - pos1.y;
	const float movedDistX = testX - movedPos1.x;
	const float movedDistY = testY - movedPos1.y;
	const float sq_distance = (movedDistX * movedDistX) + (movedDistY * movedDistY);
	
	// If no collision
	if (sq_distance >= radius * radius)
	{
		result.normal.x = 0.0f;
		result.normal.y = 0.0f;
		result.result = false;
		result.collisionTime = 1.0f;
		return result;
	}

	result.result = true;

	float difX = size1.x / 2 + size2.x / 2 - abs(movedPos2.x - movedPos1.x);
	float difY = size1.y / 2 + size2.y / 2 - abs(movedPos2.y - movedPos1.y);

	glm::vec2 diffMove1;
	glm::vec2 diffMove2;

	if (abs(distX) > abs(distY))
	{
		result.normal.x = (distX > 0.0f ? -1.0f : 1.0f);
		result.normal.y = 0.0f;

		float velsum = abs(obj1->getRigidBody()->velocity.x) + abs(obj2->getRigidBody()->velocity.x);
		float propK1 = abs(obj1->getRigidBody()->velocity.x) / velsum;
		float propK2 = abs(obj2->getRigidBody()->velocity.x) / velsum;

		diffMove1 = { -result.normal.x * (difX + abs(vel1.x) + 0.0f) * propK1, 0.0f };
		diffMove2 = { result.normal.x * (difX + abs(vel2.x) + 0.0f) * propK2, 0.0f };
	}
	else
	{
		result.normal.x = 0.0f;
		result.normal.y = (distY > 0.0f ? -1.0f : 1.0f);

		float velsum = abs(obj1->getRigidBody()->velocity.y) + abs(obj2->getRigidBody()->velocity.y);
		float propK1 = abs(obj1->getRigidBody()->velocity.y) / velsum;
		float propK2 = abs(obj2->getRigidBody()->velocity.y) / velsum;

		diffMove1 = { 0.0f, -result.normal.y * (difY + abs(vel1.y) + 0.0f) * propK1 };
		diffMove2 = { 0.0f, result.normal.y * (difY + abs(vel2.y) + 0.0f) * propK2 };
	}

	obj1->getTransform()->position += obj1->getRigidBody()->velocity - diffMove1;
	obj2->getTransform()->position += obj2->getRigidBody()->velocity - diffMove2;
	
	return result;
}

/*
std::cout << "Collision\n";
// Determine the normal
glm::vec2 dist;
glm::vec2 border;
if (abs(distX) > abs(distY))
{
	result.normal.x = (distX > 0.0f ? -1.0f : 1.0f);
	result.normal.y = 0.0f;

	border = { 0, 1 };

	dist = { abs(movedPos1.x - (movedPos2.x + result.normal.x * size2.x / 2)) * -result.normal.x, 0.0f };
}
else
{
	result.normal.x = 0.0f;
	result.normal.y = (distY > 0.0f ? -1.0f : 1.0f);

	border = { 1, 0 };

	dist = { 0.0f, abs(movedPos1.y - (movedPos2.y + result.normal.y * size2.y / 2)) * -result.normal.y };
}

float angle = acos((vel1.x * border.x + vel1.y * border.y) /
	(sqrt(vel1.x * vel1.x + vel1.y * vel1.y) * 1));
if (vel1.x == 0 && vel1.y == 0)
	angle = 0;

float odd_move = (radius + glm::dot(dist, result.normal)) / sin(angle);
float speed = sqrt(vel1.x * vel1.x + vel1.y * vel1.y);

result.collisionTime = std::clamp(1.0f - odd_move / speed, 0.0f, 0.99f);

// Fix the circle position
obj1->getTransform()->position.x += obj1->getRigidBody()->velocity.x * result.collisionTime;
obj1->getTransform()->position.y += obj1->getRigidBody()->velocity.y * result.collisionTime;

// Set new tests
testX = obj1->getTransform()->position.x;
testY = obj1->getTransform()->position.y;

// Apply the crate velocity
//obj2->getTransform()->position.x += obj2->getRigidBody()->velocity.x;
//obj2->getTransform()->position.y += obj2->getRigidBody()->velocity.y;

// Redefine positions
pos1 = obj1->getTransform()->position;
pos2 = obj2->getTransform()->position;

if (pos1.x < pos2.x - size2.x / 2) testX = pos2.x - size2.x / 2; // left edge
else if (pos1.x > pos2.x + size2.x / 2) testX = pos2.x + size2.x / 2; // right edge

if (pos1.y < pos2.y - size2.y / 2) testY = pos2.y - size2.y / 2; // top edge
else if (pos1.y > pos2.y + size2.y / 2) testY = pos2.y + size2.y / 2; // bottom edge

// dif = difference between the collision point and the center
bool moving = abs(obj2->getRigidBody()->velocity.x) > 0.01f || abs(obj2->getRigidBody()->velocity.y) > 0.01f;
float r = (float)obj1->getWidth() / 2;
glm::vec2 dif = glm::vec2(testX, testY) - obj1->getTransform()->position;
float dif_len = sqrt(dif.x * dif.x + dif.y * dif.y);
glm::vec2 dif_unit = glm::vec2(dif.x / dif_len, dif.y / dif_len);
if (dif_len < r && moving) // Circle is still inside
{
	glm::vec2 move = MAMA::Project(dif, result.normal);
	obj2->getTransform()->position += - move * 0.9f - r * result.normal;
}*/