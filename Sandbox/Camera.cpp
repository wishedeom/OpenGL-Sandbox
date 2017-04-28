#include "Camera.h"

Camera::Camera(const glm::vec3& position)
	: _position { position }
{}

glm::vec3 Camera::position() const
{
	return _position;
}

void Camera::translate(const glm::vec3& v)
{
	_position += v;
}

glm::mat4 Camera::view() const
{
	return glm::translate(glm::mat4(), _position);
}
