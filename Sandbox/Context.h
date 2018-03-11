/*
*	The Context class manages GLFW initialization and termination.
*/

#pragma once

#include "src/opengl/types.h"

#include <utility>

class Window;

class Context final
{
public:
	Context(OpenGL::Version version);
	~Context();
	void Initialize(const Window& window) const;
};
