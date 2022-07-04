#include "Scene.h"

void Scene::Cycle(double elapsedTime)
{
	Update(elapsedTime);
	RenderGraphics(elapsedTime);
}

Scene::Scene(SceneManager &sceneManager, SDL_Renderer *renderer, entt::registry &registry, AssetStore &assetStore)
	: m_sceneManager(sceneManager),
	  m_renderer(renderer),
	  m_registry(registry),
	  m_assetStore(assetStore)
{
}