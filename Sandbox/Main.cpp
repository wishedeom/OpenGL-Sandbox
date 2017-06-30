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
#include "entity.h"
#include "PointLight.h"
#include "Light.h"
#include "FragmentShader.h"
#include "gameaction.h"
#include "inputhandler.h"
#include "inputscheme.h"
#include "playercontroller.h"
#include "Material.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "VertexShader.h"
#include "Window.h"
#include "utils.h"
#include "transform.h"
#include "Mesh.h"

int main() try
{
	const Context context(OpenGL::Version{ 3, 3 });
	const Window window(1600, 900, "OpenGL Sandbox", false);
	context.initializeGLEW(window);
	Camera camera(window, { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, -1.0f });
	PlayerController controller(window, camera);
	InputScheme scheme;
	InputHandler inputHandler(controller, scheme);

	ShaderProgram shader;
	shader
		.attach(VertexShader(fromFile("simpleVertexShader.vs")))
		.attach(FragmentShader(fromFile("simpleFragmentShader.fs")))
		.link();

	const Mesh mesh =
		Mesh::Builder()
		.addVertex( { { -0.5f, -0.5f, 0.0f } } )
		.addVertex( { { -0.5f,  0.5f, 0.0f } } )
		.addVertex( { {  0.5f, -0.5f, 0.0f } } )
		.addVertex( { {  0.5f,  0.5f, 0.0f } } )
		.setIndices({0, 1, 2, 1, 3, 2})
		.build();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	GLdouble lastFrame = 0.0f;
	while (!window.shouldClose())
	{
		const GLdouble currentFrame = glfwGetTime();
		const GLdouble deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		controller.update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mesh.draw(shader, camera, glm::rotate(glm::mat4(), static_cast<float>(currentFrame), glm::vec3(0.0f, 1.0f, 0.0f)));

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
