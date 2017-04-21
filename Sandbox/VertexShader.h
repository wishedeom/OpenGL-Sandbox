#pragma once

#include "Shader.h"

class VertexShader final
	: public Shader
{
public:
	VertexShader(const std::string& source);
	~VertexShader() override;
};
