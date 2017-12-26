#pragma once

#include <optional>

class SphereCollider;

class Collision final
{
public:
	std::optional<Collision> detect(const SphereCollider& s1, const SphereCollider& s2);
};

