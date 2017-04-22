#include <array>
#include <iostream>
#include <vector>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push)
#pragma warning (disable: 4244)
#pragma warning (disable: 4456)

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma warning (pop)

#include "Context.h"
#include "FragmentShader.h"
#include "InputHandler.h"
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "Window.h"
#include "utils.h"

const std::array<GLfloat, 32> vertices =
{	// Position				// Colour			// Texture
	 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,		0.3f, 0.3f, 0.3f,	0.0f, 1.0f,
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

	ShaderProgram shaderProgram;
	shaderProgram
		.attach(VertexShader(fromFile("vertexShader.vs")))
		.attach(FragmentShader(fromFile("fragmentShader.fs")))
		.link()
		.use();

	int width, height, channels;

	stbi_set_flip_vertically_on_load(1);
	auto image = stbi_load("container.jpg", &width, &height, &channels, 0);
	GLuint texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	image = stbi_load("awesomeface.png", &width, &height, &channels, STBI_rgb);
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) (6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	shaderProgram.use();

	glClearColor(0.1f, 1.0f, 0.1f, 1.0f);

	while (!window.shouldClose())
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glUniform1i(glGetUniformLocation(shaderProgram, "uTexture0"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shaderProgram, "uTexture1"), 1);

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
