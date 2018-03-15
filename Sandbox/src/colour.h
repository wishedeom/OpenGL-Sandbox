#pragma once

#include "opengl/types.h"

struct Colour final
{
	using ValueType = OpenGL::Clampf;

	ValueType r;
	ValueType g;
	ValueType b;
	ValueType a;

	Colour(float r, float g, float b, float a);

	static const Colour Black;
};
