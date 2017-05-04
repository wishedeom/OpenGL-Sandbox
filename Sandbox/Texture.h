#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils.h"

enum class Components
	: int
{
	Default  =  0,
	RGB      =  3,
	RGBA     =  4,
};

class Texture final
{
public:
	Texture(const std::string& filename, const Components req);
	GLuint id() const;
	operator GLuint() const;

private:
	GLuint _id;
	GLsizei _width;
	GLsizei _height;
	GLsizei _channels;
};
