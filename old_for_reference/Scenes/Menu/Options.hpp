#ifndef OPTIONS_SCENE_H
#define OPTIONS_SCENE_H

#include "scenes/Scene.hpp"
#include <string>
#include <SDL2/SDL.h>

class OptionsScene : public Scene
{
private:
	SceneManager& m_localSceneManager;

	// Font Stuff
	SDL_Color m_color = {235, 235, 235};
	int m_fontSize = 48;

	Texture *m_setVolumeTexture;
	Pixel m_setVolumePixel;

	Texture *m_optionsTexture;
	Pixel m_optionsPixel;

	Texture *m_pointerTexture;
	Pixel m_pointerPixel;

	Texture *m_lineTexture;
	Pixel m_linePixel;

	// MenuController
	Pixel m_menuPos = {0, 0};
	bool m_keep_playing = true;

	bool m_VolumeActive = false;
	int orgVolume;

public:
	// Scene
	
	bool Update(double elapsedTime) override;
	void LeftMenu();
	void RenderGraphics(double elapsedTime) override;
	void Load() override;
	void Unload() override;
	OptionsScene(SceneManager& sceneManager, SceneManager& localSceneManager);

};
#endif // OPTIONS_SCENE_H