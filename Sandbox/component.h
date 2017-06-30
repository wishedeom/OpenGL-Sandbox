#pragma once

class Entity;

namespace component
{
	class Component
	{
	public:
		Component();
		Component(Entity& entity);
		virtual ~Component() = 0;

		bool isAttachedToEntity() const;
		Entity& entity() const;
		virtual void update(double) = 0 {}

	private:
		Entity* _entity;
	};
}
