#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

#include "Texture.h"

struct Material
{
	Texture diffuse;
	Texture specular;
	GLfloat shininess;
};
