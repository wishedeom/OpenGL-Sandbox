#pragma once

#include "Mesh.h"
#include "sphere.h"

#include <GLFW/glfw3.h>

#include <memory>

struct Entity
{
	Mesh mesh;
	glm::mat4 transform;
	std::unique_ptr<Collider> collider;
	glm::vec3 velocity;

	const Collider* GetCollider() const
	{
		return collider.get();
	}
};
