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
#include "Mesh.h"
#include "src/opengl/error.h"
#include "src/opengl/functions.h"
#include "src/colour.h"
#include "renderer.h"
#include "sphere.h"

int main() try
{
	const auto window = Context::Get().MakeWindow(300, 300, "OpenGL Sandbox", false);
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
	auto m = MakeSphere().Scale(2.0f);
	//auto m2 = m.Scale
	Entity e = { m, {} };

	auto plane = MakeQuad({ -20.0f, 0.0f, -20.0f }, { 20.0f, 0.0f, -20.0f }, { -20.0f, 0.0f, 20.0f });
	Entity bottomPlane { plane, glm::translate(glm::vec3 { 0.0f, -5.0f, 0.0f }) };
	//Entity topPlane { plane, glm::rotate(glm::translate(glm::vec3 { 0.0f, 5.0f, 0.0f }), pi<float>, glm::vec3 { 1.0f, 0.0f, 0.0f }) };

	e.mesh.SetColour(Colour::Grapefruit);
	bottomPlane.mesh.SetColour(Colour::White);

	const Entity* renderables[] = { &bottomPlane, /*&topPlane,*/ &e, };

	OpenGL::ClearColour(Colour::Black);

	Enable(OpenGL::Capability::DepthTest);
	Enable(OpenGL::Capability::CullFace);
	
	Renderer renderer(shader, camera);
	renderer.SetAmbientLightColour({ 1.0f, 0.5f, 0.5f, 1.0f });
	renderer.SetAmbientLightStrength(0.7f);
	
	glm::vec3 velocity = { 0.0f, 10.0f, 0.0f };
	constexpr float gravity = -9.8f;

	float lastFrame = 0.0f;
	while (!window.ShouldClose())
	{
		const float currentFrame = glfwGetTime();
		const float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		controller.Update();
		Clear(OpenGL::Buffer::Color | OpenGL::Buffer::Depth);

		//const auto s = 2.0f * static_cast<float>(std::sin(lastFrame));
		//e.transform = glm::translate(glm::mat4(), { 0.0f, s, 0.0f });
		
		Plane plane;
		plane.normal = - glm::normalize(glm::cross(bottomPlane.mesh.GetVertices()[1].position - bottomPlane.mesh.GetVertices()[0].position,
								  bottomPlane.mesh.GetVertices()[2].position - bottomPlane.mesh.GetVertices()[0].position));
		plane.point = bottomPlane.mesh.GetVertices()[0].position - glm::vec3(0.0f, 5.0f, 0.0f);

		Sphere sphere;
		sphere.radius = 2.0f;
		sphere.center = glm::vec3(e.transform[3]);

		const auto collisionDistance = Collide(sphere, plane, velocity);
		const auto displacement = velocity * deltaTime;
		const auto distanceToTravel = glm::length(displacement);

		if (std::numeric_limits<float>::epsilon() <= distanceToTravel && std::numeric_limits<float>::epsilon() <= collisionDistance && collisionDistance <= distanceToTravel)
		{
			velocity = -velocity * 0.5f;
		}
		else if (glm::length(velocity) < std::numeric_limits<float>::epsilon() || Intersection(sphere, plane) < std::numeric_limits<float>::infinity())
		{
			velocity = glm::zero<glm::vec3>();
		}
		else
		{
			velocity += gravity * deltaTime * glm::vec3 { 0.0f, 1.0f, 0.0f };
		}

		e.transform = glm::translate(e.transform, velocity * deltaTime);
		
		//const auto collisionDistance = Collide()

		for (const auto& entity : renderables)
		{
			renderer.Draw(*entity);
		}

		//renderer.Draw(e);
		//m.draw(shader, camera, t);
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
