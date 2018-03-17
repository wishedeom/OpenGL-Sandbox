#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum class InputAction
{
	None,
	APress,
	ARelease,
	DPress,
	DRelease,
	SPress,
	SRelease,
	WPress,
	WRelease,
	EscPress,
	SpacePress,
};

InputAction ToInputAction(GLint key, GLint scancode, GLint action, GLint mods);
