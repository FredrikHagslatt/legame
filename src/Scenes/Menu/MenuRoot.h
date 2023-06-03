#ifndef MENU_ROOT_H
#define MENU_ROOT_H

#include "SceneManager/Scene.h"
#include "SceneManager/SceneManager.h"

class MenuRoot : public Scene
{
private:
	SceneManager m_sceneManager;
	SDL_Rect camera;

public:
	// Scene
	void Update(const double elapsedTime) override;
	void RenderGraphics(const double elapsedTime) override;
	void Load(std::string level) override;
	void Unload() override;
	MenuRoot(SDL_Renderer *renderer, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore);
};
#endif