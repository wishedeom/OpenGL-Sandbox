#pragma once

#include <map>
#include <string>
#include <string_view>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/opengl/types.h"
#include "src/opengl/functions.h"

class Shader;

class ShaderProgram final
{
public:
	ShaderProgram();
	ShaderProgram(ShaderProgram&& rhs);
	ShaderProgram& operator=(ShaderProgram&& rhs);

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

	ShaderProgram& AttachShader(const Shader& shader) &;
	ShaderProgram& Link() &;

	ShaderProgram&& AttachShader(const Shader& shader) &&;
	ShaderProgram&& Link() &&;
	
	void Use() const;
	
	GLuint GetUniformLocation(const std::string_view& name) const;
	GLuint GetIndex() const;
	GLuint GetParameter(OpenGL::ProgramParameter parameter) const;
	
	operator GLuint() const;

	template <typename T>
	void SetUniform(const std::string_view& name, const T& value) const;

private:
	std::string GetInfoLog() const;

	GLuint m_id;
};

template <typename T>
inline void ShaderProgram::SetUniform(const std::string_view& name, const T& value) const
{
	const auto location = GetUniformLocation(name);
	if (location == -1)
	{
		return;
	}

	OpenGL::GetUniformSetter<T>()(location, 1, GL_FALSE, glm::value_ptr(value));
}
