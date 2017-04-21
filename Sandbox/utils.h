#pragma once

#include <type_traits>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLboolean toGLboolean(const bool b);

template <typename E>
auto castToUnderlying(E value)
{
	using T = std::underlying_type<E>::type;
	return static_cast<T>(value);
}
