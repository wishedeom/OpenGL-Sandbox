#include "Camera.h"
#include "ShaderProgram.h"
#include "Window.h"
#include "utils.h"

const glm::vec3 Camera::worldUp = { 0.0f, 1.0f, 0.0f };

Camera::Camera(const Window& window, const glm::vec3& position, const glm::vec3& direction)
	: _window(&window)
	, _transform(position, direction)
{}

glm::vec3 Camera::position() const
{
	return _transform.position();
}

glm::vec3 Camera::direction() const
{
	return _transform.direction();
}

glm::vec3 Camera::forward() const
{
	const auto dir = direction();
	return glm::normalize(glm::vec3(dir.x, 0.0f, dir.z));
}

glm::vec3 Camera::right() const
{
	return glm::normalize(-glm::cross(worldUp, direction()));
}

glm::vec3 Camera::up() const
{
	return glm::cross(direction(), right());
}

void Camera::translate(const glm::vec3& v)
{
	_transform.setPosition(_transform.position() + v);
}

void Camera::rotateRight(const float angleRad)
{
	_transform.setDirection(glm::rotate(direction(), -angleRad, worldUp));
}

void Camera::rotateUp(const float angleRad)
{
	_transform.setDirection(glm::rotate(direction(), -angleRad, right()));
}

GLfloat Camera::fov() const
{
	return _fov;
}

void Camera::setFov(const GLfloat f)
{
	_fov = f;
}

glm::mat4 Camera::view() const
{
	const auto pos = position();
	return glm::lookAt(pos, pos + direction(), worldUp);
}

glm::mat4 Camera::projection() const
{
	return glm::perspective(glm::radians(_fov), _window->Width() / _window->Height(), 0.1f, 1000.0f);
}

const Window& Camera::window()
{
	return *_window;
}

void Camera::bind(const ShaderProgram& shader) const
{
	glUniformMatrix4fv(shader.GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection()));
	glUniformMatrix4fv(shader.GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view()));
}
