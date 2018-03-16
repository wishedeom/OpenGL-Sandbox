#include "component.h"

Component::Component() = default;

Component::Component(Entity& entity)
	: _entity(&entity)
{}

Component::~Component() = default;

bool Component::isAttachedToEntity() const
{
	return _entity != nullptr;
}

const Entity& Component::entity() const
{
	return *_entity;
}

Entity& Component::entity()
{
	return *_entity;
}
