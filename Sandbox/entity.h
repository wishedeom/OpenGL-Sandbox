#pragma once

#pragma warning (disable : 4172)

#include <algorithm>
#include <vector>
#include <memory>
#include <optional>
#include <string>
#include <map>

#include "component.h"

class Entity final
{
	using ID = unsigned;
	using ComponentArray = std::vector<std::unique_ptr<component::Component>>;

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

	template <class C>
	bool addComponent();

	template <class C>
	std::optional<C*> tryGetComponent() const;

	template <class C>
	bool removeComponent();

private:
	template <class C>
	ComponentArray::iterator findComponent();

	const ID _id;
	std::string _name;
	ComponentArray _components;
};

template<class C>
inline bool Entity::addComponent()
{
	const auto& maybe = tryGetComponent<C>();
	if (maybe.has_value())
	{
		return false;
	}
	_components.push_back(std::make_unique<C>());
	return true;
}

template<class C>
inline std::optional<C*> Entity::tryGetComponent() const
{
	for (const auto& component : _components)
	{
		auto ptr = dynamic_cast<C*>(component.get());
		if (ptr != nullptr)
		{
			return ptr;
		}
	}
	return nullptr;
}

template<class C>
inline bool Entity::removeComponent()
{
	const auto& it = findComponent<C>();
	if (it == _components.end())
	{
		return false;
	}
	_components.erase(it);
	return true;
}

template<class C>
inline std::vector<std::unique_ptr<component::Component>>::iterator Entity::findComponent()
{
	return std::find_if(_components.begin(), _components.end(), [](const auto& component)
	{
		return dynamic_cast<C*>(component.get()) != nullptr;
	});
}
