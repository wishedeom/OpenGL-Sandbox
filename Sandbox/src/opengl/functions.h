#pragma once

#include "types.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#pragma warning (pop)

#include <string>
#include <string_view>
#include <optional>

struct Colour;

namespace OpenGL
{
	GLuint CreateProgram();
	GLint GetShaderParameter(GLuint shaderID, ShaderParameter paramName);
	GLint GetProgramParameter(GLuint programID, ProgramParameter parameter);
	void LinkProgram(GLuint programID);

	std::string GetProgramInfoLog(GLuint programID);
	std::string GetShaderInfoLog(GLuint programID);

	void AttachShader(GLuint programID, GLuint shaderID);
	void UseProgram(GLuint programID);
	std::optional<GLuint> GetUniformLocation(GLuint programID, const std::string_view& uniformName);

	GLuint CreateShader();
	void ClearColour(const Colour& colour);

	void Enable(Capability cap);
	void Disable(Capability cap);
	void Clear(Buffer buffer);

	template <typename T>
	auto GetUniformSetter();
}

template <>
inline auto OpenGL::GetUniformSetter<glm::mat4>()
{
	return glUniformMatrix4fv;
}
