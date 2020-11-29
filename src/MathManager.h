#pragma once
#ifndef __MATHMANAGER_H__
#define __MATHMANAGER_H__
#include <glm/detail/type_vec2.hpp>

class MathManager
{
public:
	static constexpr float PI = 3.14159265359f;
	
	static float RadToDeg(float rad);
	static float DegToRad(float deg);

	static float To180Deg(float deg);

	static glm::vec2 Project(glm::vec2 to_project, glm::vec2 axis);
	static float DotProduct(glm::vec2 A, glm::vec2 B);
	static glm::vec2 Parallel(float length, glm::vec2 axis);
	
private:

	
};

typedef MathManager MAMA;

#endif