#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "InputHandler.h"
#include "Window.h"

void keyCallback(GLFWwindow* const window, const GLint key, const GLint scancode, const GLint action, const GLint mode);

InputHandler::InputHandler(const Window& window)
{
	glfwSetKeyCallback(window.get(), keyCallback);
}

void keyCallback(GLFWwindow* const window, const GLint key, const GLint, const GLint action, const GLint)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}