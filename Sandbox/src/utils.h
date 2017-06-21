#pragma once

#include <type_traits>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

// Reads the entire contents of a file into a string
std::string fromFile(const std::string& filename);

void checkShaderCompilationErrors(const GLuint id, const ShaderType type);

// Converts an enum class value to its underlying integral value
template <typename E>
constexpr auto toIntegral(E value) -> typename std::underlying_type<E>::type
{
	return static_cast<std::underlying_type<E>::type>(value);
}
