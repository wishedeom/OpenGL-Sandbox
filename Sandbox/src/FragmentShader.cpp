#include "FragmentShader.h"

FragmentShader::FragmentShader(const std::string& source)
	: Shader { source, ShaderType::Fragment }
{}

FragmentShader::~FragmentShader() {}
