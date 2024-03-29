#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "SceneManager/Scene.h"
#include "Events/KeyPressedEvent.h"

class MainMenu : public Scene
{
private:
	SDL_Rect m_camera;

public:
	void OnKeyPressedEvent(const KeyPressedEvent event);

	// Scene
	void Update(const double elapsedTime) override;
	void RenderGraphics(const double elapsedTime) override;
	void Load(std::string level) override;
	void Unload() override;
	using Scene::Scene;
};
#endif // MAIN_MENU_H