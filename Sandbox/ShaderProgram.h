#pragma once

#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader;

enum class UniformType
{
	Float4,
};

struct Uniform
{
	GLuint id;
	UniformType type;
	
	operator GLuint() const
	{
		return id;
	}
};

class ShaderProgram final
{
public:
	ShaderProgram();
	ShaderProgram& attach(const Shader& shader);
	ShaderProgram& link();
	ShaderProgram& use();
	Uniform addUniform(const std::string& name, const UniformType type);
	Uniform uniform(const std::string& name) const;
	GLuint index() const;
	operator GLuint() const;

private:
	GLuint _id;
	std::map<std::string, Uniform> _uniforms;
};
