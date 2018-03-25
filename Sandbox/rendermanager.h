#pragma once

#include "entity.h"
#include "renderer.h"

#include <vector>
#include <memory>
#include <map>

class RenderManager final
{
public:
	template <typename R, typename... Args>
	R& AddRenderer(Args&&... args);

	void RegisterEntity(const Renderer& renderer, const Entity& entity);

	void Draw() const;

private:
	using Renderers = std::vector<std::unique_ptr<Renderer>>;
	using Entities = std::vector<const Entity*>;
	using EntityMap = std::map<const Renderer*, Entities>;

	Renderers m_renderers;
	EntityMap m_entityMap;
};

template <typename R, typename... Args>
inline R& RenderManager::AddRenderer(Args&&... args)
{
	m_renderers.push_back(std::make_unique<R>(std::forward<Args>(args)...));
	const auto renderer = m_renderers.back().get();
	m_entityMap[renderer];
	return *renderer;
}
