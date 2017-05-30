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
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Light.h"
#include "FragmentShader.h"
#include "InputAction.h"
#include "InputHandler.h"
#include "Material.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "VertexShader.h"
#include "Window.h"
#include "utils.h"

const std::array<GLfloat, (3 + 3 + 2) * 6 * 6> vertices =
{	// Position           // Normal            // Texture
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

int main() try
{
	const Context context(OpenGL::Version{ 3, 3 });
	const Window window(1600, 900, "OpenGL Sandbox");
	context.initializeGLEW(window);
	Camera camera(window, { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, -1.0f });
	PlayerController inputHandler(window, camera);

	ShaderProgram shader;
	shader
		.attach(VertexShader(fromFile("vertexShader.vs")))
		.attach(FragmentShader(fromFile("fragmentShader.fs")))
		.link();

	ShaderProgram lampShader;
	lampShader
		.attach(VertexShader(fromFile("vertexShader.vs")))
		.attach(FragmentShader(fromFile("lamp.fs")))
		.link();

	const Material crate
	{
		{ "container2.png",          Components::RGB, Texture::Type::Diffuse  },  // Diffuse map
		{ "container2_specular.png", Components::RGB, Texture::Type::Specular },  // Specular map
		0.4f                                                                      // Shininess
	};

	// Cube models
	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) (6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	// Light
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	const GLint viewPosLoc = shader.getUniform("viewPos");

	const GLint lightPosLoc = glGetUniformLocation(shader, "directionalLight.direction");
	glm::vec3 lightPos = { -0.2f, -1.0f, -0.3f };

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Set uniforms
	shader.use();
	const auto modelLoc = shader.getUniform("model");
	const auto projectionLoc = shader.getUniform("projection");
	const auto viewLoc = shader.getUniform("view");

	// Materials
	glUniform1f(shader.getUniform("material.shininess"), crate.shininess);

	glUniform1i(shader.getUniform("material.diffuse"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, crate.diffuse);

	glUniform1i(shader.getUniform("material.specular"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, crate.specular);

	// Light values
	glUniform3f(shader.getUniform("directionalLight.colours.ambient"), 0.1f, 0.1f, 0.1f);
	glUniform3f(shader.getUniform("directionalLight.colours.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(shader.getUniform("directionalLight.colours.specular"), 0.5f, 0.0f, 0.0f);

	// Attenuation
	//glUniform1f(shader.getUniform("light.constant"), 1.0f);
	//glUniform1f(shader.getUniform("light.linear"),   0.09f);
	//glUniform1f(shader.getUniform("light.quadratic"), 0.0032f);

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

		lampShader.use();
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

		shader.use();
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
