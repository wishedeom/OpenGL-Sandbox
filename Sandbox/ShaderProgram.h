#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader;

class ShaderProgram final
{
public:
	ShaderProgram();
	void attach(const Shader& shader) const;
	void link() const;
	void use() const;

private:
	GLuint _index;
};
