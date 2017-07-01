#pragma once

#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader;

class ShaderProgram final
{
public:
	ShaderProgram();
	ShaderProgram& attach(const Shader& shader);
	ShaderProgram& link();
	void use() const;
	GLuint getUniform(const std::string& name) const;
	GLuint index() const;
	operator GLuint() const;

private:
	GLuint _id;
};
