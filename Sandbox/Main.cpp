#include <array>
#include <iostream>
#include <vector>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
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
#include "src/opengl/functions.h"
#include "src/colour.h"

int main() try
{
	const auto window = Context::Get().MakeWindow(900, 900, "OpenGL Sandbox", false);
	Camera camera(window, { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, -1.0f });
	PlayerController controller(window, camera);
	InputScheme scheme;
	InputHandler inputHandler(controller, scheme);

	const auto shader = ShaderProgram()
						.AttachShader(VertexShader(util::ReadFile("simpleVertexShader.vs")))
						.AttachShader(FragmentShader(util::ReadFile("simpleFragmentShader.fs")))
						.Link();

	//auto m = MakeQuad();
	//auto m = MakeCube();
	auto m = MakeSphere();
	auto p = MakeQuad({ -5.0f, -1.0f, -5.0f }, { 5.0f, -1.0f, -5.0f }, { -5.0f, -1.0f, 5.0f });

	OpenGL::ClearColour(Colour::Black);

	Enable(OpenGL::Capability::DepthTest);
	//Enable(OpenGL::Capability::CullFace);

	GLdouble lastFrame = 0.0f;
	while (!window.ShouldClose())
	{
		const GLdouble currentFrame = glfwGetTime();
		const GLdouble deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		controller.update();
		Clear(OpenGL::Buffer::Color | OpenGL::Buffer::Depth);

		const auto s = 2.0f * static_cast<float>(std::sin(lastFrame));
		const auto t = glm::translate(glm::mat4(), { 0.0f, s, 0.0f });

		m.draw(shader, camera, t);
		//p.draw(shader, camera/*, t2*/);

		window.SwapBuffers();
	}

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what();
	std::cin.get();
	return -1;
}
