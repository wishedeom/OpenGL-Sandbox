#pragma once

#include "opengl/types.h"

#include <cstdint>

using uint8 = uint8_t;

struct Colour final
{
	using ValueType = OpenGL::Clampf;

	ValueType r;
	ValueType g;
	ValueType b;
	ValueType a;

	Colour(float r, float g, float b, float a);

	static Colour From8Bit(uint8 r, uint8 g, uint8 b, uint8 a);

	static const Colour Black;
	static const Colour White;
	static const Colour Grapefruit;
};
