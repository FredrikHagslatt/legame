#include "Scene.h"
#include <memory>

/*
void Scene::Cycle(const double elapsedTime)
{
	Update(elapsedTime);
	RenderGraphics(elapsedTime);
}
*/

Scene::Scene(SDL_Renderer *renderer, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore)
	: m_renderer(renderer),
	  m_registry(registry),
	  m_assetStore(assetStore)
{
}