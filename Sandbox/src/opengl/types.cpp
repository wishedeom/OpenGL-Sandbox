#include "types.h"
#include "../../utils.h"

OpenGL::Buffer OpenGL::operator|(const Buffer lhs, const Buffer rhs)
{
	return Buffer(util::to_underlying(lhs) | util::to_underlying(rhs));
}