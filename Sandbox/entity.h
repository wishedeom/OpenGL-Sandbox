#pragma once

#pragma warning (disable : 4172)

#include <algorithm>
#include <vector>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <map>
#include <stdexcept>

#include "component.h"

class Entity
{
	using IDType = size_t;
	using ComponentPtr = std::unique_ptr<Component>;
	using Components = std::vector<ComponentPtr>;

	static IDType s_nextID;
	static std::map<IDType, Entity*> s_entityRegistry;

public:
	static Entity* Get(IDType id);

	template <typename ComponentType, typename EntityType>
	static ComponentType* GetComponent(EntityType& entity);

	Entity(const std::string_view& name = "");
	~Entity();

	Entity(const Entity& entity) = delete;
	Entity(Entity&&) = default;

	Entity& operator=(const Entity&) = delete;
	Entity& operator=(Entity&&) = delete;

	IDType ID() const;

	const std::string& Name() const;
	std::string Name();

	template <typename ComponentType, typename... Args>
	ComponentType& AddComponent(Args&&... args);

	template <typename ComponentType>
	const ComponentType* GetComponent() const;

	template <typename ComponentType>
	ComponentType* GetComponent();

	template <typename ComponentType>
	void RemoveComponent();

	void Update(double deltaTime);

private:
	template <typename ComponentType>
	Components::iterator FindComponent();

	const IDType m_id;
	std::string m_name;
	Components m_components;
};

template <typename ComponentType, typename... Args>
inline ComponentType& Entity::AddComponent(Args&&... args)
{
	const auto it = FindComponent<ComponentType>();
	if (it != m_components.end())
	{
		throw std::runtime_exception("Component already exists.");
	}

	m_components.push_back(std::make_unique<ComponentType>(*this, std::forward<Args>(args)...));
	return *m_components.back();
}

template <typename ComponentType, typename EntityType>
inline ComponentType* Entity::GetComponent(EntityType& entity)
{
	static_assert(std::is_base_of_v<Component, ComponentType>);

	for (const auto& component : entity.m_components)
	{
		const auto ptr = dynamic_cast<ComponentType*>(component.get());
		if (ptr != nullptr)
		{
			return ptr;
		}
	}
	return nullptr;
}

template <typename ComponentType>
inline const ComponentType* Entity::GetComponent() const
{
	//for (const auto& component : m_components)
	//{
	//	auto* const ptr = dynamic_cast<ComponentType*>(component.get());
	//	if (ptr != nullptr)
	//	{
	//		return ptr;
	//	}
	//}
	//return nullptr;

	return GetComponent<const ComponentType>(*this);
}

template<typename ComponentType>
inline ComponentType* Entity::GetComponent()
{
	return GetComponent<ComponentType>(*this);
}

template <typename ComponentType>
inline void Entity::RemoveComponent()
{
	const auto& it = FindComponent<ComponentType>();
	if (it == m_components.end())
	{
		return;
	}

	m_components.erase(it);
}

template <typename ComponentType>
inline Entity::Components::iterator Entity::FindComponent()
{
	return std::find_if(m_components.begin(), m_components.end(), [](const auto& component)
	{
		return dynamic_cast<ComponentType*>(component.get()) != nullptr;
	});
}
