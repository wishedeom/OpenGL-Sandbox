#include "physics.h"
#include "entity.h"
#include "transform.h"

component::Physics::Physics(Entity& entity)
	: Component(entity)
{}

component::Physics::~Physics() = default;

void component::Physics::update(const double deltaTime)
{
	static constexpr float g = -9.8f;
	using namespace component;
	auto& transform = entity().get<Transform>();

	_velocity.z += g * static_cast<float>(deltaTime);
	transform.position() += _velocity;
}
