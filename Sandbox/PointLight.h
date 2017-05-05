#pragma once

#include "Light.h"

struct PointLight final
	: Light
{
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
};
