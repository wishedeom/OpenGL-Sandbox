#include <array>
#include <iostream>
#include <vector>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning (pop)

#include "Camera.h"
#include "Context.h"
#include "FragmentShader.h"
#include "InputHandler.h"
#include "ShaderProgram.h"
#include "Texture.h"
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
	const Context context(OpenGL::Version{ 3, 3 }, OpenGL::Profile::Core, Resizable::True);
	const Window window(800, 600, "Learn OpenGL");
	context.initializeGLEW(window, GLEWExperimental::True);
	Camera camera({ 0.0f, 0.0f, -5.0f });
	InputHandler inputHandler(window, camera);

	ShaderProgram shaderProgram;
	shaderProgram
		.attach(VertexShader(fromFile("vertexShader.vs")))
		.attach(FragmentShader(fromFile("fragmentShader.fs")))
		.link()
		.use();

	Texture container("container.jpg", RequiredComponents::RGB);
	Texture awesomeFace("awesomeface.png", RequiredComponents::RGB);

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

	glm::mat4 transform;
	const auto transformLoc = glGetUniformLocation(shaderProgram, "transform");
	const auto projection = window.projectionMatrix();
	const auto projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	const auto viewLoc = glGetUniformLocation(shaderProgram, "view");

	while (!window.shouldClose())
	{
		glfwPollEvents();
		inputHandler.update();
		glClear(GL_COLOR_BUFFER_BIT);

		transform = glm::rotate(transform, glm::radians(0.05f), { 1.0f, 0.0f, 0.0f });
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view()));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, container);
		glUniform1i(glGetUniformLocation(shaderProgram, "uTexture0"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, awesomeFace);
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
