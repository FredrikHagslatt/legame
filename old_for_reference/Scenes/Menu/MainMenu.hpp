#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "scenes/Scene.hpp"
#include "scenes/SceneManager.hpp"

class MainMenu : public Scene
{
private:
	SceneManager& m_localSceneManager;

	// Font Stuff
	SDL_Color m_color {235, 235, 235};
	int m_fontSize = 72;

	Texture *m_hubTexture;
	Pixel m_hubPixel;

	Texture *m_mapEditorTexture;
	Pixel m_mapEditorPixel;

	Texture *m_optionsTexture;
	Pixel m_optionsPixel;

	Texture *m_pointerTexture;
	Pixel m_pointerPixel;

	// MenuController
	int m_menuPos = 0;

	enum
	{
		QUIT_GAME,
		CONTINUE_GAME
	};

public:
	// Scene
	bool Update(double elapsedTime) override;
	void RenderGraphics(double elapsedTime) override;
	void Load() override;
	void Unload() override;
	MainMenu(SceneManager& sceneManager, SceneManager& localSceneManager);
};
#endif // MAIN_MENU_H