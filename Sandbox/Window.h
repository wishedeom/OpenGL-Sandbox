#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window final
{
public:
	Window(const GLint height, const GLint width, const std::string& title);
	void makeContextCurrent() const;
	bool shouldClose() const;
	void swapBuffers() const;

private:
	GLFWwindow* _window;
	GLint _height;
	GLint _width;
};
