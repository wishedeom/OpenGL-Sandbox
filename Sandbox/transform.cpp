#include "transform.h"

#pragma warning (push, 0)
#include <glm/gtc/matrix_transform.hpp>
#pragma warning (pop, 0)

const glm::vec3 worldUp = { 0.0f, 1.0f, 0.0f };

component::Transform::Transform(const glm::vec3& position, const glm::vec3& direction)
	: _position(position)
	, _direction(direction)
{}

component::Transform::Transform(Entity& entity, const glm::vec3& position, const glm::vec3& direction)
	: Component(entity)
	, _position(position)
	, _direction(direction)
{}

glm::mat4 component::Transform::matrix() const
{
	//const auto pos = position();
	//return glm::translate(glm::lookAt(pos, pos + direction(), worldUp), position());
	static const glm::vec3 initial = { 0.0f, 1.0f, 0.0f };
	const auto v = glm::cross(direction(), initial);
	const float angle = acos(glm::dot(initial, direction()) / (glm::length(initial) * glm::length(direction())));

	return angle == 0.0f ? glm::translate(glm::mat4(), position()): glm::rotate(glm::translate(glm::mat4(), position()), angle, v);

}

glm::vec3 component::Transform::position() const
{
	return _position;
}

glm::vec3 component::Transform::direction() const
{
	return _direction;
}

glm::vec3 component::Transform::forward() const
{
	return glm::normalize(glm::vec3(_direction.x, 0.0f, _direction.z));
}

glm::vec3 component::Transform::right() const
{
	return glm::normalize(-glm::cross(worldUp, _direction));
}

glm::vec3 component::Transform::up() const
{
	return glm::cross(_direction, right());
}

void component::Transform::setPosition(const glm::vec3& position)
{
	_position = position;
}

void component::Transform::setDirection(const glm::vec3& direction)
{
	_direction = direction;
}

void component::Transform::update(double deltaTime)
{
	Component::update(deltaTime);
}
