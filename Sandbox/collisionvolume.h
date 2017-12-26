#pragma once

#include "component.h"

class Entity;

namespace component
{
	class CollisionVolume
		: public Component
	{
	public:
		CollisionVolume(Entity& entity);
		virtual ~CollisionVolume();
	};
}

