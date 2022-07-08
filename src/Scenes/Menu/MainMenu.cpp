#include "MainMenu.h"
#include "Constants.h"
#include "Logger/Logger.h"

#include "Components/Tags.h"
#include "Components/TextLabel.h"

#include "Systems/RenderTextSystem.h"

void MainMenu::Update(double elapsedTime)
{
	/*
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode)
					{
					case SDL_SCANCODE_W:
					case SDL_SCANCODE_UP:
						if (m_menuPos > 0)
							m_menuPos--;
						break;
					case SDL_SCANCODE_S:
					case SDL_SCANCODE_DOWN:
						if (m_menuPos < 2)
							m_menuPos++;
						break;
					case SDL_SCANCODE_KP_ENTER:
					case SDL_SCANCODE_RETURN:
						switch (m_menuPos)
						{
						case 0:
						{
							m_sceneManager.QueueSceneChange("HUB");
							break;
						}
						case 1:
						{
							m_sceneManager.QueueSceneChange("MAPEDITOR");
							break;
						}
						case 2:
						{
							m_localSceneManager.QueueSceneChange("OPTIONS");
							break;
						}
	m_pointerPixel.y = SCREENHEIGHT / 2 - 0.8f * m_hubTexture->height() + m_hubTexture->height() * m_menuPos;
	return CONTINUE_GAME;
		*/
}

void MainMenu::RenderGraphics(double elapsedTime)
{
	SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
	SDL_RenderClear(m_renderer);

	/*
		g_gfx.ResetRenderArea();
		g_gfx.RenderRaw(*m_hubTexture, m_hubPixel);
		g_gfx.RenderRaw(*m_mapEditorTexture, m_mapEditorPixel);
		g_gfx.RenderRaw(*m_optionsTexture, m_optionsPixel);
		g_gfx.RenderRaw(*m_pointerTexture, m_pointerPixel);
		g_gfx.RenderBuffer();
	*/
	RenderTextSystem::Update(m_registry, m_renderer, m_assetStore, camera);

	SDL_RenderPresent(m_renderer);
}
void MainMenu::Load()
{
	Logger::Info("[MainMenu] Loading Scene");

	m_assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
	camera = {0, 0, 0, 0};

	const auto label = m_registry->create();
	m_registry->emplace<UI_Tag>(label);
	SDL_Color green = {30, 200, 30};
	m_registry->emplace<TextLabel>(label, vec2f(WINDOWWIDTH / 2 - 40, 10), "- Main Menu - ", "charriot-font", green, true);
}

void MainMenu::Unload()
{

	/*
		m_hubPixel.x = (SCREENWIDTH - m_hubTexture->width()) / 2;
		m_hubPixel.y = SCREENHEIGHT / 2 - m_hubTexture->height();

		m_mapEditorPixel.x = (SCREENWIDTH - m_hubTexture->width()) / 2; // Aligned to Hub on purpose
		m_mapEditorPixel.y = SCREENHEIGHT / 2;

		m_optionsPixel.x = (SCREENWIDTH - m_hubTexture->width()) / 2; // Aligned to Hub on purpose
		m_optionsPixel.y = SCREENHEIGHT / 2 + m_hubTexture->height();

		m_pointerTexture->Scale(2.0f);
		m_pointerPixel.x = (SCREENWIDTH - m_hubTexture->width()) / 2 - 2 * m_pointerTexture->width();
	*/
}
