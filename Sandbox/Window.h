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
	Window(const GLint height, const GLint width, const std::string& title);
	void makeContextCurrent() const;
	void close() const;
	bool shouldClose() const;
	void swapBuffers() const;
	GLFWwindow* get() const;
	glm::mat4 projectionMatrix() const;

private:
	GLFWwindow* _window;
	GLfloat _height;
	GLfloat _width;
};
