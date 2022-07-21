#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "SceneManager/Scene.h"
#include "Events/KeyPressedEvent.h"

class MainMenu : public Scene
{
private:
	SDL_Rect m_camera;
	entt::entity m_menuNavigator;

public:
	void OnKeyPressedEvent(const KeyPressedEvent event);

	// Scene
	void Update(const double elapsedTime) override;
	void RenderGraphics(const double elapsedTime) override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;
};
#endif // MAIN_MENU_H