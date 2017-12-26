#pragma once

#pragma warning (push, 0)
#include "glm/glm.hpp"
#pragma warning (pop, 0)

#include "collisionvolume.h"

namespace component
{
	class SphereCollider final
		: public CollisionVolume
	{
	public:
		SphereCollider(Entity& entity);
		virtual ~SphereCollider() override;

		void setRadius(float radius);
		
		glm::vec3 centre() const;
		float radius() const;

		bool contains(const glm::vec3& point) const;

	private:
		float _radius;
	};
}
