#include "Camera.h"
#include "Window.h"

const glm::vec3 Camera::worldUp = { 0.0f, 1.0f, 0.0f };

Camera::Camera(const Window& window, const glm::vec3& position, const glm::vec3& direction)
	: _window { &window }
	, _position { position }
	, _direction { direction }
{}

glm::vec3 Camera::position() const
{
	return _position;
}

glm::vec3 Camera::direction() const
{
	return _direction;
}

glm::vec3 Camera::forward() const
{
	return glm::normalize(glm::vec3(_direction.x, 0.0f, _direction.z));
}

glm::vec3 Camera::right() const
{
	return glm::normalize(-glm::cross(worldUp, _direction));
}

glm::vec3 Camera::up() const
{
	return glm::cross(_direction, right());
}

void Camera::translate(const glm::vec3& v)
{
	_position += v;
}

void Camera::rotateRight(const float angleRad)
{
	_direction = glm::rotate(_direction, -angleRad, worldUp);
}

void Camera::rotateUp(const float angleRad)
{
	_direction = glm::rotate(_direction, -angleRad, right());
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
	return glm::lookAt(_position, _position + _direction, worldUp);
}

glm::mat4 Camera::projection() const
{
	return glm::perspective(glm::radians(_fov), _window->width() / _window->height(), 0.1f, 1000.0f);
}

const Window& Camera::window()
{
	return *_window;
}
