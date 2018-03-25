#include "collisionmanager.h"
#include "sphere.h"

#pragma warning (push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#pragma warning (pop)

void CollisionManager::RegisterEntity(const Entity& entity)
{
	m_entities.push_back(&entity);
}

auto CollisionManager::CheckCollision(const Entity& entity) -> CollisionResult
{
	const auto* const collider = entity.GetCollider();
	if (collider == nullptr)
	{
		return {};
	}

	CollisionResult result;
	for (const auto& checkedEntity : m_entities)
	{
		const auto* const checkedCollider = checkedEntity->GetCollider();
		if (checkedCollider == nullptr)
		{
			continue;
		}

		const auto collision = ::Collide(*collider, *checkedCollider);
		if (!collision.valid)
		{
			continue;
		}

		result[checkedEntity] = collision;
	}

	return result;
}
