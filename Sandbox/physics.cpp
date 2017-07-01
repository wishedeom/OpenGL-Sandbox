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

	_velocity.y += g * static_cast<float>(deltaTime);
	transform.setPosition(transform.position() + _velocity * static_cast<float>(deltaTime));
}
