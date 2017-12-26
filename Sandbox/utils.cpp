#include <fstream>
#include <iostream>
#include <sstream>

#include "utils.h"

std::string util::fromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		throw std::runtime_error("File '" + filename + "'not found.");
	}
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

void util::checkShaderCompilationErrors(const GLuint id, const ShaderType type)
{
	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_TRUE)
	{
		return;
	}
	GLint length;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
	auto infoLog = new GLchar[length];
	glGetShaderInfoLog(id, sizeof(GLchar) * length, nullptr, infoLog);
	std::string infoString(infoLog);
	delete[] infoLog;
	throw std::runtime_error("Error: " + shaderTypeNames.at(type) + " shader compilation failed.\n" + infoString + '\n');
}

void util::reportOpenGLErrors()
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "OpenGL error: " << err << '\n';
	}
}
