#include "colour.h"

Colour::Colour(const float r, const float g, const float b, const float a)
	: r(r), g(g), b(b), a(a)
{}

Colour::operator glm::vec3() const
{
	return { r, g, b };
}

Colour Colour::From8Bit(const uint8 r, const uint8 g, const uint8 b, const uint8 a)
{
	return { r / 256.0f, g / 256.0f, b / 256.0f, a / 256.0f };
}

const Colour Colour::Black = { 0.0f, 0.0f, 0.0f, 1.0f };
const Colour Colour::White = { 1.0f, 1.0f, 1.0f, 1.0f };
const Colour Colour::Grapefruit = Colour::From8Bit(255, 7, 100, 255);
