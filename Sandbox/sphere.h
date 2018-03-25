#pragma once

#include <glm/glm.hpp>

#include <optional>

template <typename T>
constexpr auto epsilon = std::numeric_limits<T>::epsilon();

struct Collision
{
	bool valid = false;
	float distance = 0;
	glm::vec3 point = { 0.0f, 0.0f, 0.0f };
};

const Collision NoCollision;

class PlaneCollider;
class SphereCollider;

class Collider
{
public:
	enum class Type
	{
		Sphere,
		Plane,
	};

	virtual Type GetType() const = 0;
	virtual glm::vec3 Normal(const glm::vec3& position) const = 0;
};

template <Collider::Type type>
class ColliderImpl
	: public Collider
{
	virtual Type GetType() const override
	{
		return type;
	}
};

class NotOnColliderSurface
	: public std::exception
{
public:
	virtual const char* what() const override
	{
		return "Point is not on collider surface.";
	}
};

class SphereCollider
	: public ColliderImpl<Collider::Type::Sphere>
{
public:
	glm::vec3 center;
	float radius;

	virtual glm::vec3 Normal(const glm::vec3& position) const override
	{
		const auto delta = position - center;
		const auto distanceToCenter = glm::length(delta);
		if (std::abs(distanceToCenter - radius) > epsilon<float>)
		{
			throw NotOnColliderSurface();
		}

		return glm::normalize(delta);
	}
};

class PlaneCollider
	: public ColliderImpl<Collider::Type::Plane>
{
public:
	glm::vec3 normal;
	glm::vec3 origin;

	virtual glm::vec3 Normal(const glm::vec3& position) const override
	{
		return normal;
	}
};

struct Ray
{
	glm::vec3 origin = { 0.0f, 0.0f, 0.0f };
	glm::vec3 direction = { 0.0f, 0.0f, 0.0f };

	Ray() {}

	Ray(const glm::vec3& origin, const glm::vec3& direction)
		: origin(origin)
		, direction(direction)
	{}
};

inline float Intersection(const Ray& ray, const PlaneCollider& plane)
{
	if (glm::length(plane.normal) < std::numeric_limits<float>::epsilon())
	{
		return std::numeric_limits<float>::infinity();
	}

	const auto planeNormal = glm::normalize(plane.normal);
	const auto lineDirection = glm::normalize(ray.direction);
	const auto delta = plane.origin - ray.origin;

	const auto dot = glm::dot(planeNormal, lineDirection);
	if (dot == 0.0f)
	{
		return std::numeric_limits<float>::infinity();
	}

	return glm::dot(delta, planeNormal) / glm::dot(planeNormal, lineDirection);
}

inline float Intersection(const SphereCollider& sphere, const PlaneCollider& plane)
{
	Ray line;
	line.origin = sphere.center;
	line.direction = -glm::normalize(plane.normal);

	const auto centerDistance = Intersection(line, plane);

	if (centerDistance > sphere.radius)
	{
		return std::numeric_limits<float>::infinity();
	}

	return sphere.radius - centerDistance;
}

inline Collision Collide(const SphereCollider& dynamicSphere, const PlaneCollider& staticPlane)
{
	Ray ray;
	ray.origin = dynamicSphere.center;
	//ray.direction = direction;

	const auto centerDistance = Intersection(ray, staticPlane);
	const auto distance = centerDistance - dynamicSphere.radius;

	return { true, distance };
}


Collision Collide(const Collider& dynamicCollider, const Collider& staticCollider);

template <typename C1, typename C2>
Collision Collide(const Collider& dynamicCollider, const Collider& staticCollider)
{
	return Collide(static_cast<const C1&>(dynamicCollider), static_cast<const C2&>(staticCollider));
}

inline Collision Collide(const Collider& dynamicCollider, const Collider& staticCollider)
{
	using Type = Collider::Type;

	switch (dynamicCollider.GetType())
	{
		case Type::Sphere:
		{
			switch (staticCollider.GetType())
			{
				case Type::Plane:
					return Collide<SphereCollider, PlaneCollider>(dynamicCollider, staticCollider);
					//return Collide(static_cast<const SphereCollider&>(dynamicCollider), static_cast<const PlaneCollider&>(staticCollider), direction);
			}
		}
	}

	return NoCollision;
}
