#pragma once

#include "Light.h"

struct DirectionalLight final
	: Light
{
	glm::vec3 direction;
};
