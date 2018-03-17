#pragma once

#include <map>
#include <string>
#include <string_view>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/opengl/types.h"
#include "src/opengl/functions.h"
#include "src/opengl/uniformsetters.h"

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

	void SetUniformMat4(const std::string_view& name, const glm::mat4& matrix) const;

private:
	std::string GetInfoLog() const;

	GLuint m_id;
};
