#pragma once

#include <string>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum class ShaderType
	: GLenum
{
	Vertex    =  GL_VERTEX_SHADER,
	Fragment  =  GL_FRAGMENT_SHADER,
};

const std::map<ShaderType, std::string> shaderTypeNames
{
	{ ShaderType::Vertex,   "vertex"   },
	{ ShaderType::Fragment, "fragment" },
};

class Shader
{
public:
	Shader(const std::string& source, const ShaderType type);
	virtual ~Shader() = 0;
	GLuint index() const;
	operator GLuint() const;

private:
	GLuint _id;
};
