#pragma once

#include "Shader.h"

class FragmentShader final
	: public Shader
{
public:
	FragmentShader(const std::string& source);
	virtual ~FragmentShader() override = default;
};
