#pragma once

#include "src/opengl/types.h"

#include <string>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
	using ShaderType = OpenGL::ShaderType;

public:
	Shader(const std::string& source, const OpenGL::ShaderType type);
	virtual ~Shader() = 0;
	GLuint index() const;
	operator GLuint() const;

private:
	GLuint _id;
};
