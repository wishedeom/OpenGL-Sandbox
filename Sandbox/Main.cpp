#include <iostream>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Context.h"
#include "Window.h"

int main() try
{
	Context context({ 3, 3 }, OpenGLProfile::Core, Resizable::True);
	Window window(800, 600, "Learn OpenGL");
	context.initializeGLEW(window, GLEWExperimental::True);

	while (!window.shouldClose())
	{
		glfwPollEvents();
		window.swapBuffers();
	}

	return 0;
}
catch (const std::runtime_error& e)
{
	std::cout << e.what();
	return -1;
}
