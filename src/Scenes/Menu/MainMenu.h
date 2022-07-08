#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "SceneManager/Scene.h"

class MainMenu : public Scene
{
private:
	SDL_Rect camera;
	// Font Stuff
	/*
		SDL_Color m_color{235, 235, 235};
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
	*/

public:
	// Scene
	void Update(double elapsedTime) override;
	void RenderGraphics(double elapsedTime) override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;
};
#endif // MAIN_MENU_H