#pragma once

#pragma warning (push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

#include "component.h"

namespace component
{
	class Transform final
		: public Component
	{
	public:
		Transform(const glm::vec3& position = {}, const glm::vec3& direction = { 0.0f, 1.0f, 0.0f });
		Transform(Entity& entity, const glm::vec3& position = {}, const glm::vec3& direction = { 0.0f, 1.0f, 0.0f });
		virtual ~Transform() override = default;

		glm::mat4 matrix() const;
		
		glm::vec3 position() const;
		glm::vec3 direction() const;
		glm::vec3 forward() const;
		glm::vec3 right() const;
		glm::vec3 up() const;

		void setPosition(const glm::vec3& position);
		void setDirection(const glm::vec3& direction);

		virtual void Update(double deltaTime) override;

	private:
		glm::vec3 _position;
		glm::vec3 _direction;
	};
}
