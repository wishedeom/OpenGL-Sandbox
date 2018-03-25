#pragma once

#include "entity.h"

#include <vector>
#include <exception>
#include <map>

class CollisionManager final
{
public:
	using CollisionResult = std::map<const Entity*, Collision>;

	void RegisterEntity(const Entity& entity);
	CollisionResult CheckCollision(const Entity& entity);

private:
	using Entities = std::vector<const Entity*>;
	Entities m_entities;
};
