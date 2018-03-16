#include "entity.h"

Entity::IDType Entity::s_nextID = 0;
std::map<Entity::IDType, Entity*> Entity::s_entityRegistry;

Entity* Entity::Get(const IDType id)
{
	const auto it = s_entityRegistry.find(id);
	if (it == s_entityRegistry.end())
	{
		return nullptr;
	}
	return it->second;
}

Entity::Entity(const std::string_view& name /*= ""*/)
	: m_id(s_nextID++)
	, m_name(name)
{
	s_entityRegistry[m_id] = this;
}

Entity::~Entity()
{
	s_entityRegistry.erase(s_entityRegistry.find(m_id));
}

Entity::IDType Entity::ID() const
{
	return m_id;
}

const std::string& Entity::Name() const
{
	return m_name;
}

std::string Entity::Name()
{
	return m_name;
}

void Entity::Update(const double deltaTime)
{
	for (const auto& component : m_components)
	{
		component->Update(deltaTime);
	}
}
