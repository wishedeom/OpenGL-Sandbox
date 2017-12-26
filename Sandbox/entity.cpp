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
	: m_id(_nextID++)
	, m_name(name)
{
	_entityRegistry[m_id] = this;
}

Entity::Entity(const Entity& entity)
	: Entity(entity.m_name)
{
	//for (const auto& component : entity._components)
	//{
	//	
	//}
}

Entity::~Entity()
{
	_entityRegistry.erase(_entityRegistry.find(m_id));
}

size_t Entity::id() const
{
	return m_id;
}

const std::string& Entity::name() const
{
	return m_name;
}

std::string Entity::name()
{
	return m_name;
}

void Entity::setName(const std::string& name)
{
	m_name = name;
}

void Entity::update(const double deltaTime)
{
	for (const auto& component : m_components)
	{
		component->update(deltaTime);
	}
}
