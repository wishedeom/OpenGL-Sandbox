#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader;

class ShaderProgram final
{
public:
	ShaderProgram();
	const ShaderProgram& attach(const Shader& shader) const;
	const ShaderProgram& link() const;
	const ShaderProgram& use() const;
	GLuint index() const;
	operator GLuint() const;

private:
	GLuint _index;
};
