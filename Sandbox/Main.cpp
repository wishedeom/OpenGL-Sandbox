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
#include <glm/gtc/random.hpp>
#pragma warning (pop)

#include "Camera.h"
#include "Context.h"
#include "FragmentShader.h"
#include "InputHandler.h"
#include "Material.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "VertexShader.h"
#include "Window.h"
#include "utils.h"

using Colour = glm::vec3;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 colour;
	glm::vec2 texture;
};

const std::array<GLfloat, 6 * 6 * 6> vertices =
{	// Position				// Normal
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f
};

int main() try
{
	const Context context(OpenGL::Version{ 3, 3 });
	const Window window(1600, 900, "OpenGL Sandbox");
	context.initializeGLEW(window);
	Camera camera(window, { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, -1.0f });
	InputHandler inputHandler(window, camera);

	ShaderProgram shaderProgram;
	shaderProgram
		.attach(VertexShader(fromFile("vertexShader.vs")))
		.attach(FragmentShader(fromFile("fragmentShader.fs")))
		.link();

	ShaderProgram lampShader;
	lampShader
		.attach(VertexShader(fromFile("vertexShader.vs")))
		.attach(FragmentShader(fromFile("lamp.fs")))
		.link();

	const Material gold
	{
		{ 0.24725f,  0.1995f,   0.0745f   },  // Ambient
		{ 0.75164f,  0.60648f,  0.22648f  },  // Diffuse
		{ 0.628281f, 0.555802f, 0.366065f },  // Specular
		0.4f                                  // Shininess
	};

	// Cube models
	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// Light
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	const GLint viewPosLoc = shaderProgram.getUniform("viewPos");

	const GLint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
	glm::vec3 lightPos = { 1.2f, 1.0f, 2.0f };

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Set uniforms
	shaderProgram();
	const auto modelLoc = shaderProgram.getUniform("model");
	const auto projectionLoc = shaderProgram.getUniform("projection");
	const auto viewLoc = shaderProgram.getUniform("view");

	// Materials
	glUniform3fv(shaderProgram.getUniform("material.ambient"), 1, glm::value_ptr(gold.ambient));
	glUniform3fv(shaderProgram.getUniform("material.diffuse"), 1, glm::value_ptr(gold.diffuse));
	glUniform3fv(shaderProgram.getUniform("material.specular"), 1, glm::value_ptr(gold.specular));
	glUniform1f(shaderProgram.getUniform("material.shininess"), gold.shininess);

	// Light values
	glUniform3f(shaderProgram.getUniform("light.ambient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(shaderProgram.getUniform("light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(shaderProgram.getUniform("light.specular"), 1.0f, 1.0f, 1.0f);

	// Lamp
	const auto lightModelLoc = lampShader.getUniform("model");
	const auto lightProjectionLoc = lampShader.getUniform("projection");
	const auto lightViewLoc = lampShader.getUniform("view");

	glEnable(GL_DEPTH_TEST);

	const size_t numCubes = 50;
	const float radius = 15.0f;
	std::array<glm::vec3, numCubes> positions;
	std::array<glm::vec3, numCubes> axes;

	for (size_t i = 0; i < numCubes; ++i)
	{
		positions[i] = glm::ballRand(radius);
		axes[i] = glm::ballRand(1.0f);
	}

	GLdouble lastFrame = 0.0f;
	while (!window.shouldClose())
	{
		const GLdouble currentFrame = glfwGetTime();
		const GLdouble deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		inputHandler.update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lampShader();
		lightPos = glm::vec3(glm::sin(currentFrame), glm::cos(currentFrame), 0.0f);
		{
			glm::mat4 model;
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f));
			glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(model));
		}
		glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, glm::value_ptr(camera.view()));
		glUniformMatrix4fv(lightProjectionLoc, 1, GL_FALSE, glm::value_ptr(camera.projection()));

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		shaderProgram();
		const auto projection = camera.projection();
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view()));
		const auto viewPos = camera.position();
		glUniform3f(viewPosLoc, viewPos.x, viewPos.y, viewPos.z);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

		glBindVertexArray(VAO);
		for (size_t i = 0; i < numCubes; ++i)
		{
			glm::mat4 model;
			model = glm::translate(model, positions[i]);
			model = glm::rotate(model, glm::radians(5.0f * (i + 1) * static_cast<float>(currentFrame)), axes[i]);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		window.swapBuffers();
	}

	return 0;
}
catch (const std::runtime_error& e)
{
	std::cout << e.what();
	std::cin.get();
	return -1;
}
