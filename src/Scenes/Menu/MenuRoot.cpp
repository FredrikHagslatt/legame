#include "MenuRoot.h"
#include "MainMenu.h"
//#include "Scenes/Options.h"

void MenuRoot::Update(double elapsedTime)
{
	m_sceneManager.Cycle(elapsedTime);
}

void MenuRoot::RenderGraphics(double elapsedTime)
{
}

void MenuRoot::Load()
{
	m_sceneManager.AddScene("MainMenu", std::make_shared<MainMenu>(m_renderer, m_registry, m_assetStore));
	// m_sceneManager.AddScene("OPTIONS", new OptionsScene(m_sceneManager, m_local_sceneManager));

	m_sceneManager.QueueSceneChange("MainMenu");

	// g_sfx.LoadMusic("ambient", "assets/sound/music/chill/ambient_loop.wav");
	// g_sfx.PlayMusic("ambient");
}

void MenuRoot::Unload()
{
	m_sceneManager.ClearScenes();
	// g_sfx.StopMusic();
	// g_sfx.FreeAll();
}

MenuRoot::MenuRoot(SDL_Renderer *renderer, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore)
	: Scene(renderer, registry, assetStore),
	  m_sceneManager(SceneManager("MenuRoot"))
{
}