#include "MenuRoot.h"
#include "MainMenu.h"
//#include "Scenes/Options.h"
#include "Systems/MenuNavigationSystem.h"
#include "Events/EventDispatcher.h"

void MenuRoot::Update(const double elapsedTime)
{
	m_sceneManager.Update(elapsedTime);
}

void MenuRoot::RenderGraphics(const double elapsedTime)
{
	m_sceneManager.RenderGraphics(elapsedTime);
}

void MenuRoot::Load()
{
	m_sceneManager.AddScene("MainMenu", std::make_shared<MainMenu>(m_renderer, m_registry, m_assetStore));
	// m_sceneManager.AddScene("OPTIONS", new OptionsScene(m_sceneManager, m_local_sceneManager));

	m_sceneManager.QueueSceneChange("MainMenu");
	Event::dispatcher.sink<KeyPressedEvent>().connect<&MenuNavigationSystem::OnKeyPressedEvent>();

	// g_sfx.LoadMusic("ambient", "assets/sound/music/chill/ambient_loop.wav");
	// g_sfx.PlayMusic("ambient");
}

void MenuRoot::Unload()
{
	Event::dispatcher.sink<KeyPressedEvent>().disconnect<&MenuNavigationSystem::OnKeyPressedEvent>();
	m_sceneManager.ClearScenes();

	// g_sfx.StopMusic();
	// g_sfx.FreeAll();
}

MenuRoot::MenuRoot(SDL_Renderer *renderer, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore)
	: Scene(renderer, registry, assetStore),
	  m_sceneManager(SceneManager("MenuRoot"))
{
}
