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
	const auto maybeTransform = entity().tryGetComponent<Transform>();

	if (!maybeTransform.has_value())
	{
		return;
	}
	auto& transform = **maybeTransform;

	_velocity.y += g * static_cast<float>(deltaTime);
	const auto potentialNewPosition = transform.position() + _velocity * static_cast<float>(deltaTime);
	if (potentialNewPosition.y <= -10.0f)
	{
		_velocity.y = -_velocity.y * 0.9f;
	}
	else
	{
		transform.setPosition(potentialNewPosition);
	}
}
