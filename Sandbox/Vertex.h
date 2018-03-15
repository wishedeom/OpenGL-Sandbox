#pragma once

#pragma warning (push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

struct Vertex final
{
	glm::vec3 position;
	//glm::vec3 normal;
	//glm::vec2 texture;

	Vertex(const glm::vec3& position)
		: position(position)
	{}

	Vertex(const std::initializer_list<float>& coordinates)
		: position(coordinates.begin()[0], coordinates.begin()[1], coordinates.begin()[2])
	{}
};
