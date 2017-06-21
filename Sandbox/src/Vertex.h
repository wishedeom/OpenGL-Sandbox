#pragma once

#pragma warning (push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

struct Vertex final
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
};
