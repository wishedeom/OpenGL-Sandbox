#include "VAOBinding.h"

VAOBinding::VAOBinding(GLuint index)
{
	glBindVertexArray(index);
}

VAOBinding::~VAOBinding()
{
	glBindVertexArray(0);
}
