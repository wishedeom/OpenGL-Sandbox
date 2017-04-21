#pragma once

#include <type_traits>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::string fromFile(const std::string& filename);

template <typename E>
auto castToUnderlying(E value)
{
	using T = std::underlying_type<E>::type;
	return static_cast<T>(value);
}
