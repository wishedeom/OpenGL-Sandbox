#pragma once

#include <GL/glew.h>

#define DEFINE_STRONG_OGL_BOOL(name) \
enum class name                      \
	: GLboolean                      \
{                                    \
	True = GL_TRUE,                  \
	False = GL_FALSE,                \
}
