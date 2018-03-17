#pragma once

#include <glm/glm.hpp>

struct Sphere
{
	glm::vec3 center;
	float radius;
};

struct Plane
{
	glm::vec3 normal;
	glm::vec3 point;
};

struct Ray
{
	glm::vec3 direction;
	glm::vec3 point;
};

inline float Intersection(const Ray& ray, const Plane& plane)
{
	if (glm::length(plane.normal) < std::numeric_limits<float>::epsilon())
	{
		return std::numeric_limits<float>::infinity();
	}

	const auto planeNormal = glm::normalize(plane.normal);
	const auto lineDirection = glm::normalize(ray.direction);
	const auto delta = plane.point - ray.point;

	const auto dot = glm::dot(planeNormal, lineDirection);
	if (dot == 0.0f)
	{
		return std::numeric_limits<float>::infinity();
	}

	return glm::dot(delta, planeNormal) / glm::dot(planeNormal, lineDirection);
}

inline float Intersection(const Sphere& sphere, const Plane& plane)
{
	Ray line;
	line.point = sphere.center;
	line.direction = -glm::normalize(plane.normal);

	const auto centerDistance = Intersection(line, plane);

	if (centerDistance > sphere.radius)
	{
		return std::numeric_limits<float>::infinity();
	}

	return sphere.radius - centerDistance;
}

inline float Collide(const Sphere& sphere, const Plane& plane, const glm::vec3& direction)
{
	Ray ray;
	ray.point = sphere.center;
	ray.direction = direction;

	const auto centerDistance = Intersection(ray, plane);

	return centerDistance - sphere.radius;
}
