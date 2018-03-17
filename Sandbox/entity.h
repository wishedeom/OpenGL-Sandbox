#pragma once

#include "Mesh.h"

#include <GLFW/glfw3.h>

struct Entity
{
	Mesh mesh;
	glm::mat4 transform;
};
