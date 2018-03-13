#pragma once

#include <type_traits>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "src/opengl/types.h"

namespace util
{
	// Reads the entire contents of a file into a string
	std::string ReadFile(const std::string& filename);

	void CheckShaderCompilationErrors(GLuint id, OpenGL::ShaderType type);

	// Converts an enum class value to its underlying integral value
	template <typename E>
	constexpr auto to_underlying(const E value)
	{
		return static_cast<std::underlying_type_t<E>>(value);
	}
}
