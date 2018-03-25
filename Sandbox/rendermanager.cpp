#include "rendermanager.h"

void RenderManager::RegisterEntity(const Renderer& renderer, const Entity& entity)
{
	m_entityMap[&renderer].push_back(&entity);
}

void RenderManager::Draw() const
{
	for (const auto& [renderer, entities] : m_entityMap)
	{
		for (const auto& entity : entities)
		{
			renderer->Draw(*entity);
		}
	}
}
