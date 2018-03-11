#pragma once

#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/opengl/types.h"

class Shader;

class ShaderProgram final
{
public:
	ShaderProgram();
	ShaderProgram& AttachShader(const Shader& shader);
	ShaderProgram& Link();
	
	void Use() const;
	
	GLuint GetUniformLocation(const std::string& name) const;
	GLuint GetIndex() const;
	GLuint GetParameter(OpenGL::ProgramParameter parameter) const;
	
	operator GLuint() const;

private:
	std::string GetInfoLog() const;

	GLuint m_id;
};
