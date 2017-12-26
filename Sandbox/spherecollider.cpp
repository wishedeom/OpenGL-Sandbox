#include <stdexcept>

#include "spherecollider.h"
#include "entity.h"
#include "transform.h"

using namespace component;

component::SphereCollider::SphereCollider(Entity& entity)
	: CollisionVolume(entity)
	, _radius()
{}

SphereCollider::~SphereCollider() = default;

void component::SphereCollider::setRadius(const float radius)
{
	if (radius <= 0.0f)
	{
		throw std::runtime_error("Sphere radius must be positive.");
	}
	_radius = radius;
}

glm::vec3 component::SphereCollider::centre() const
{
	return entity().get<Transform>().position();
}

float component::SphereCollider::radius() const
{
	return _radius;
}

bool component::SphereCollider::contains(const glm::vec3& point) const
{
	return glm::distance(point, entity().get<Transform>().position()) <= _radius;
}
