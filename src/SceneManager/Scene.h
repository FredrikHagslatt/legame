#ifndef SCENE_H
#define SCENE_H

#include <string>
#include "entt/entt.hpp"
#include "AssetStore/AssetStore.h"

class Scene
{
public:
	std::shared_ptr<entt::registry> m_registry;
	std::shared_ptr<AssetStore> m_assetStore;
	SDL_Renderer *m_renderer;

	virtual void Update(const double elapsedTime) = 0;
	virtual void RenderGraphics(const double elapsedTime) = 0;
	virtual void Load(std::string level) = 0; // Load sprites and audio needed for the scene
	virtual void Unload() = 0;				  // Unload sprites and audio to avoid memory leaks

	// void Cycle(const double elapsedTime);
	Scene(SDL_Renderer *renderer, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore);
};
#endif // SCENE_H