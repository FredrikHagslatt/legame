#ifndef MENU_ROOT_H
#define MENU_ROOT_H

#include "scenes/Scene.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "GraphicsManager.hpp"
#include "SoundManager.hpp"
#include "scenes/SceneManager.hpp"

class MenuRoot : public Scene
{
private:
	SceneManager m_local_sceneManager;
public:
	// Scene
	bool Update(double elapsedTime) override;
	void RenderGraphics(double elapsedTime) override;
	void Load() override;
	void Unload() override;
	MenuRoot(SceneManager& sceneManager);
//	using Scene::Scene;
};
#endif