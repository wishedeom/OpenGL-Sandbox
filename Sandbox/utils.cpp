#include <fstream>
#include <iostream>
#include <sstream>

#include "utils.h"
#include "Shader.h"
#include "src/opengl/functions.h"
#include "src/opengl/types.h"

std::string util::ReadFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		throw std::runtime_error("File '" + filename + "' not found.");
	}
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

void util::CheckShaderCompilationErrors(const GLuint id, const OpenGL::ShaderType type)
{
	using namespace OpenGL;

	const bool success = GetShaderParameter(id, ShaderParameter::CompileStatus);
	if (success)
	{
		return;
	}

	const auto infoLog = GetShaderInfoLog(id);

	throw std::runtime_error("Error: " + std::string(ToString(type)) + " shader compilation failed.\n" + infoLog + '\n');
}
