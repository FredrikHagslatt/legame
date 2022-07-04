#ifndef SCENE_H
#define SCENE_H

#include "entt/entt.hpp"
#include "AssetStore/AssetStore.h"

class SceneManager;
class Scene
{
public:
	SceneManager &m_sceneManager;
	entt::registry &m_registry;
	AssetStore &m_assetStore;
	SDL_Renderer *m_renderer;

	virtual void Update(double elapsedTime) = 0;
	virtual void RenderGraphics(double elapsedTime) = 0;
	virtual void Load() = 0;   // Load sprites and audio needed for the scene
	virtual void Unload() = 0; // Unload sprites and audio to avoid memory leaks
	void Cycle(double elapsedTime);
	Scene(SceneManager &sceneManager, SDL_Renderer *renderer, entt::registry &registry, AssetStore &assetStore);
};
#endif // SCENE_H