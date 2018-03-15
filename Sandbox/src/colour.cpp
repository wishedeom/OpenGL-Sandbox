#include "colour.h"

Colour::Colour(const float r, const float g, const float b, const float a)
	: r(r)
	, g(g)
	, b(b)
	, a(a)
{}

const Colour Colour::Black = { 0.0f, 0.0f, 0.0f, 1.0f };
