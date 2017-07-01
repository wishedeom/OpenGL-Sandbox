#include "entity.h"

Entity::ID Entity::_nextID = 0;
std::map<Entity::ID, Entity*> Entity::_entityRegistry;

std::optional<Entity*> Entity::get(const ID id)
{
	const auto& it = _entityRegistry.find(id);
	if (it == _entityRegistry.end())
	{
		return {};
	}
	return it->second;
}

Entity::Entity(const std::string& name /*= ""*/)
	: _id(_nextID++)
	, _name(name)
{
	_entityRegistry[_id] = this;
}

Entity::Entity(const Entity& entity)
	: Entity(entity._name)
{
	//for (const auto& component : entity._components)
	//{
	//	
	//}
}

Entity::~Entity()
{
	_entityRegistry.erase(_entityRegistry.find(_id));
}

size_t Entity::id() const
{
	return _id;
}

const std::string& Entity::name() const
{
	return _name;
}

std::string Entity::name()
{
	return _name;
}

void Entity::setName(const std::string& name)
{
	_name = name;
}

void Entity::update(const double deltaTime)
{
	for (const auto& component : _components)
	{
		component->update(deltaTime);
	}
}
