#include "component.h"

using namespace component;

component::Component::Component() = default;

component::Component::Component(Entity& entity)
	: _entity(&entity)
{}

Component::~Component() = default;

bool component::Component::isAttachedToEntity() const
{
	return _entity != nullptr;
}

Entity& component::Component::entity() const
{
	return *_entity;
}
