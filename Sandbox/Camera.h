#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#pragma warning (pop)

#include "entity.h"
#include "transform.h"

class ShaderProgram;
class Window;

class Camera final
{
public:
	static const glm::vec3 worldUp;

	Camera(const Window& window, const glm::vec3& position, const glm::vec3& direction);
	glm::vec3 position() const;
	glm::vec3 direction() const;
	glm::vec3 forward() const;
	glm::vec3 right() const;
	glm::vec3 up() const;
	void translate(const glm::vec3& v);
	void rotateRight(const float angleRad);
	void rotateUp(const float angleRad);
	GLfloat fov() const;
	void setFov(const GLfloat f);
	glm::mat4 view() const;
	glm::mat4 projection() const;
	const Window& window();

	void bind(const ShaderProgram& shader) const;

private:
	const Window* _window;
	component::Transform _transform;
	GLfloat _fov = 45.0f;
};
