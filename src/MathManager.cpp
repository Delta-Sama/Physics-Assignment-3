#include "MathManager.h"
#include <algorithm>

float MathManager::RadToDeg(float rad)
{
	return ((rad / MAMA::PI) * 180.0f);
}

float MathManager::DegToRad(float deg)
{
	return ((deg / 180.0f) * MAMA::PI);
}

float MathManager::To180Deg(float deg)
{
	while (abs(deg) > 360.0f)
	{
		deg += 360.0f * ( deg > 0 ? -1 : 1 );
	}
	if (abs(deg) > 180.0f)
	{
		deg += 360.0f * (deg > 0 ? -1 : 1);
	}
	return deg;
}

glm::vec2 MathManager::Project(glm::vec2 to_project, glm::vec2 axis)
{
	
	const float axis_len = sqrt(axis.x * axis.x + axis.y * axis.y);
	const glm::vec2 axis_unit = glm::vec2(axis.x / axis_len, axis.y / axis_len);
	float proj = to_project.x * axis_unit.x + to_project.y * axis_unit.y;
	return glm::vec2(axis_unit.x * proj, axis_unit.y * proj);
}

glm::vec2 MathManager::Parallel(float length, glm::vec2 axis)
{
	const float axis_len = sqrt(axis.x * axis.x + axis.y * axis.y);
	const glm::vec2 axis_unit = glm::vec2(axis.x / axis_len, axis.y / axis_len);
	return glm::vec2(axis_unit.x * length, axis_unit.y * length);
}

float MathManager::DotProduct(glm::vec2 A, glm::vec2 B)
{
	return A.x * B.x + A.y * B.y;
}
