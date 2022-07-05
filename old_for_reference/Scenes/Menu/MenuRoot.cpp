#include "MenuRoot.hpp"
#include "MainMenu.hpp"
#include "Options.hpp"
#include "Constants.hpp"
#include "scenes/SceneManager.hpp"

bool MenuRoot::Update(double elapsedTime)
{
	return m_local_sceneManager.Cycle(elapsedTime);
}

void MenuRoot::RenderGraphics(double elapsedTime)
{
}

void MenuRoot::Load()
{
	g_sfx.LoadMusic("ambient", "assets/sound/music/chill/ambient_loop.wav");
	g_sfx.PlayMusic("ambient");
}

void MenuRoot::Unload()
{
	g_sfx.StopMusic();
	g_sfx.FreeAll();
}

MenuRoot::MenuRoot(SceneManager &sceneManager)
	: Scene(sceneManager),
	  m_local_sceneManager()
{
	m_local_sceneManager.AddScene("MAINMENU", new MainMenu(m_sceneManager, m_local_sceneManager));
	m_local_sceneManager.AddScene("OPTIONS", new OptionsScene(m_sceneManager, m_local_sceneManager));
	m_local_sceneManager.ChangeScene("MAINMENU");
}
