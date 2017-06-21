#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push, 0)
#include <glm/gtc/matrix_transform.hpp>
#pragma warning (pop)

class Window final
{
public:
	Window(GLint height, GLint width, const std::string& title, bool fullScreen = true);
	void makeContextCurrent() const;
	void close() const;
	bool shouldClose() const;
	void swapBuffers() const;
	operator GLFWwindow*() const;
	GLFWwindow* get() const;
	GLfloat height() const;
	GLfloat width() const;

private:
	GLFWwindow* _window;
	GLfloat _height;
	GLfloat _width;
};
