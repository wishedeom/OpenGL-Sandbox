#pragma once

#include "Shader.h"

class VertexShader final
	: public Shader
{
public:
	VertexShader(const std::string& source);
	virtual ~VertexShader() override = default;
};
