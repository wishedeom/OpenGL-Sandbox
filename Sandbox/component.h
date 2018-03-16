#pragma once

class Entity;

class Component
{
public:
	Component();
	Component(Entity& entity);
	virtual ~Component() = 0;

	bool isAttachedToEntity() const;
	const Entity& entity() const;
	Entity& entity();
	virtual void Update(double) = 0 {}

private:
	Entity* _entity;
};
