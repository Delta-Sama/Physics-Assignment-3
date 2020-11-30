#include "PhysicsManager.h"

#include <algorithm>


#include "MathManager.h"
#include "Util.h"

std::list<GameObject*> PhysicsManager::m_physical_objects;

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager() = default;

void PhysicsManager::AddPhysicalObject(GameObject& obj)
{
	m_physical_objects.push_back(&obj);
}

float PhysicsManager::CheckWorldCollision(GameObject& obj)
{
	for (std::list<GameObject*>::iterator it = PhysicsManager::GetPhysicalObjects()->begin();
		it != PhysicsManager::GetPhysicalObjects()->end(); it++)
	{
		if (*it != &obj)
		{
			GameObject* A = &obj;
			GameObject* B = *it;
			
			static glm::vec2 last_normal = {0.0f,0.0f};
			
			Manifold result = ADCOMA::SweptAABB(&obj, *it);

			const float e = std::min(A->getRigidBody()->elasticity,B->getRigidBody()->elasticity);

			if (abs(result.normal.x) > 0.0001f)
			{
				float m1 = A->getRigidBody()->mass;
				float m2 = B->getRigidBody()->mass;

				glm::vec2 normalVel1 = MAMA::Project(A->getRigidBody()->velocity, result.normal);
				glm::vec2 normalVel2 = MAMA::Project(B->getRigidBody()->velocity, result.normal);

				glm::vec2 vel1 = ((m1 - m2) * normalVel1 + 2 * m2 * normalVel2) / (m1 + m2);
				glm::vec2 vel2 = ((m2 - m1) * normalVel2 + 2 * m1 * normalVel1) / (m1 + m2);

				A->getRigidBody()->velocity = vel1 + glm::vec2(0.0f, A->getRigidBody()->velocity.y);
				B->getRigidBody()->velocity = vel2 + glm::vec2(0.0f, B->getRigidBody()->velocity.y);
			}
			
			if (abs(result.normal.y) > 0.0001f)
			{
				float m1 = A->getRigidBody()->mass;
				float m2 = B->getRigidBody()->mass;

				glm::vec2 normalVel1 = MAMA::Project(A->getRigidBody()->velocity, result.normal);
				glm::vec2 normalVel2 = MAMA::Project(B->getRigidBody()->velocity, result.normal);

				glm::vec2 vel1 = ((m1 - m2) * normalVel1 + 2 * m2 * normalVel2) / (m1 + m2);
				glm::vec2 vel2 = ((m2 - m1) * normalVel2 + 2 * m1 * normalVel1) / (m1 + m2);
				
				A->getRigidBody()->velocity = vel1 + glm::vec2(A->getRigidBody()->velocity.x, 0.0f);
				B->getRigidBody()->velocity = vel2 + glm::vec2(B->getRigidBody()->velocity.x, 0.0f);
			}

			Util::QueueLine(obj.getTransform()->position, obj.getTransform()->position + obj.getRigidBody()->velocity * 10.0f, { 0,1,0,1 });
			Util::QueueLine((*it)->getTransform()->position, (*it)->getTransform()->position + (*it)->getRigidBody()->velocity * 10.0f, { 0,0,1,1 });
			
			if (result.result)
			{
				last_normal = result.normal;
				bool x_opposite_vel = (A->getRigidBody()->velocity.x > 0 && B->getRigidBody()->velocity.x < 0 ||
					A->getRigidBody()->velocity.x < 0 && B->getRigidBody()->velocity.x > 0);

				bool y_opposite_vel = (A->getRigidBody()->velocity.y > 0 && B->getRigidBody()->velocity.y < 0 ||
					A->getRigidBody()->velocity.y < 0 && B->getRigidBody()->velocity.y > 0);

				if (x_opposite_vel) {
					A->getRigidBody()->velocity.x *= A->getRigidBody()->elasticity;
					B->getRigidBody()->velocity.x *= B->getRigidBody()->elasticity;
				}

				if (y_opposite_vel) {
					A->getRigidBody()->velocity.y *= A->getRigidBody()->elasticity;
					B->getRigidBody()->velocity.y *= B->getRigidBody()->elasticity;
				}
			}

			Util::QueueCircle({ 800.0f,350.0f }, 2, { 0,0,1,1 });
			Util::QueueLine({ 800.0f,350.0f }, glm::vec2(800.0f, 350.0f) + last_normal * 20.0f, { 0,0,1,1 });

			}
	}

	return 0.0f;
}
