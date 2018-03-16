#pragma once

#pragma warning (push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

#include "component.h"

namespace component
{
	class Physics final
		: public Component
	{
	public:
		Physics(Entity& entity);
		~Physics();

		virtual void Update(double deltaTime) override;

	private:
		glm::vec3 _velocity;
	};
}
