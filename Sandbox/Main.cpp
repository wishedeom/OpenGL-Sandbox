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
#include "physics.h"
#include "src/opengl/error.h"

int main() try
{
	const Context context(OpenGL::Version{ 3, 3 });
	const Window window(1600, 900, "OpenGL Sandbox", false);
	context.Initialize(window);
	Camera camera(window, { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, -1.0f });
	PlayerController controller(window, camera);
	InputScheme scheme;
	InputHandler inputHandler(controller, scheme);

	OpenGL::ClearErrorFlag();
	auto shader = ShaderProgram()
					.AttachShader(VertexShader(util::fromFile("simpleVertexShader.vs")))
					.AttachShader(FragmentShader(util::fromFile("simpleFragmentShader.fs")))
					.Link();

	Entity testEntity;

	testEntity.add<component::Transform>();
	
	testEntity.add<component::Mesh>();
	testEntity.get<component::Mesh>().setVertices
	({
		{{ -0.5f, -0.5f, 0.0f }},
		{{ -0.5f,  0.5f, 0.0f }},
		{{  0.5f, -0.5f, 0.0f }},
		{{  0.5f,  0.5f, 0.0f }},
	});
	testEntity.get<component::Mesh>().setIndices({ 0, 1, 2, 1, 3, 2 });
	//testEntity.get<component::Mesh>() = component::Mesh(testEntity, component::Mesh::Data::makeSquare());
	//testEntity.add<component::Physics>();

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

		testEntity.update(deltaTime);
		testEntity.get<component::Mesh>().draw(shader, camera);

		window.swapBuffers();
	}

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what();
	std::cin.get();
	return -1;
}
