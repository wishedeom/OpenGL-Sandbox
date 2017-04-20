#include <iostream>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Context.h"

namespace config
{
	constexpr std::pair<int, int> version = { 3, 3 };
}

int main()
{
	Context context({ 3, 3 }, OpenGLProfile::Core, Resizable::True);

	auto window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create OpenGL window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW.\n";
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;
}
