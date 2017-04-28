#pragma once

#pragma warning (push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning (pop)

class Camera final
{
public:
	Camera(const glm::vec3& position = {});
	Camera(const Camera&) = delete;

	glm::vec3 position() const;
	void translate(const glm::vec3& v);
	glm::mat4 view() const;

private:
	glm::vec3 _position;
};
