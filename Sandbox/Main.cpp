#include <array>
#include <iostream>
#include <vector>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Context.h"
#include "FragmentShader.h"
#include "InputHandler.h"
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "Window.h"
#include "utils.h"

const std::array<GLfloat, 12> vertices =
{
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
};

const std::array<GLuint, 6> indices =
{
	0, 1, 3,
	1, 2, 3,
};

int main() try
{
	const Context context(OpenGLVersion{ 3, 3 }, OpenGLProfile::Core, Resizable::True);
	const Window window(800, 600, "Learn OpenGL");
	context.initializeGLEW(window, GLEWExperimental::True);
	const InputHandler inputHandler(window);

	const ShaderProgram shaderProgram;
	shaderProgram
		.attach(VertexShader(fromFile("vertexShader.vs")))
		.attach(FragmentShader(fromFile("fragmentShader.fs")))
		.link()
		.use();

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	shaderProgram.use();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while (!window.shouldClose())
	{
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		window.swapBuffers();
	}

	return 0;
}
catch (const std::runtime_error& e)
{
	std::cout << e.what();
	return -1;
}
