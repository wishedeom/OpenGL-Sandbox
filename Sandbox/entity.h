#pragma once

#pragma warning (disable : 4172)

#include <algorithm>
#include <vector>
#include <memory>
#include <optional>
#include <string>
#include <map>

#include "component.h"

class Entity
{
	using ID = unsigned;
	using ComponentCollection = std::vector<std::unique_ptr<component::Component>>;

	static ID _nextID;
	static std::map<ID, Entity*> _entityRegistry;

public:
	static std::optional<Entity*> get(ID id);

	Entity(const std::string& name = "");
	~Entity();

	Entity(const Entity& entity);
	Entity(Entity&&) = delete;

	Entity& operator=(const Entity&) = delete;
	Entity& operator=(Entity&&) = delete;

	ID id() const;

	const std::string& name() const;
	std::string name();

	void setName(const std::string& name);

	template <typename ComponentType, typename... Args>
	bool AddComponent(Args&&... args);

	template <typename C>
	C* GetComponent() const;

	template <typename C>
	C& get() const;

	template <typename C>
	bool removeComponent();

	void update(double deltaTime);

private:
	template <typename C>
	ComponentCollection::iterator findComponent();

	const ID m_id;
	std::string m_name;
	ComponentCollection m_components;
};

template <typename ComponentType, typename... Args>
inline bool Entity::AddComponent(Args&&... args)
{
	const auto component = GetComponent<ComponentType>();
	if (component != nullptr)
	{
		return false;
	}

	m_components.push_back(std::make_unique<ComponentType>(*this, std::forward<Args>(args)...));
	return true;
}

template <typename C>
inline C* Entity::GetComponent() const
{
	for (const auto& component : m_components)
	{
		const auto ptr = dynamic_cast<C*>(component.get());
		if (ptr != nullptr)
		{
			return ptr;
		}
	}
	return nullptr;
}

template<typename C>
inline C& Entity::get() const
{
	return *GetComponent<C>();
}

template<typename C>
inline bool Entity::removeComponent()
{
	const auto& it = findComponent<C>();
	if (it == m_components.end())
	{
		return false;
	}
	m_components.erase(it);
	return true;
}

template<typename C>
inline std::vector<std::unique_ptr<component::Component>>::iterator Entity::findComponent()
{
	return std::find_if(m_components.begin(), m_components.end(), [](const auto& component)
	{
		return dynamic_cast<C*>(component.get()) != nullptr;
	});
}
