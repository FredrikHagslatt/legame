#include "MainMenu.hpp"
#include "Constants.hpp"
#include <iostream>

bool MainMenu::Update(double elapsedTime)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return QUIT_GAME;
			break;
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
				}
				break;
			case SDL_SCANCODE_ESCAPE:
				return QUIT_GAME;
			}
		}
	}
	m_pointerPixel.y = SCREENHEIGHT / 2 - 0.8f * m_hubTexture->height() + m_hubTexture->height() * m_menuPos;
	return CONTINUE_GAME;
}

void MainMenu::RenderGraphics(double elapsedTime)
{
	g_gfx.ResetRenderArea();
	g_gfx.RenderRaw(*m_hubTexture, m_hubPixel);
	g_gfx.RenderRaw(*m_mapEditorTexture, m_mapEditorPixel);
	g_gfx.RenderRaw(*m_optionsTexture, m_optionsPixel);
	g_gfx.RenderRaw(*m_pointerTexture, m_pointerPixel);
	g_gfx.RenderBuffer();
}

void MainMenu::Load()
{
}

void MainMenu::Unload()
{
	TTF_Quit();
}

MainMenu::MainMenu(SceneManager &sceneManager, SceneManager &localSceneManager)
	: Scene(sceneManager),
	  m_localSceneManager(localSceneManager),
	  m_hubTexture(g_gfx.RequestTexture("Enter the hub", m_fontSize, m_color)),
	  m_mapEditorTexture(g_gfx.RequestTexture("Map editor", m_fontSize, m_color)),
	  m_optionsTexture(g_gfx.RequestTexture("Options", m_fontSize, m_color)),
	  m_pointerTexture(g_gfx.RequestTexture("assets/sprites/misc/smiley.png", 1, 1))
{

	m_hubPixel.x = (SCREENWIDTH - m_hubTexture->width()) / 2;
	m_hubPixel.y = SCREENHEIGHT / 2 - m_hubTexture->height();

	m_mapEditorPixel.x = (SCREENWIDTH - m_hubTexture->width()) / 2; // Aligned to Hub on purpose
	m_mapEditorPixel.y = SCREENHEIGHT / 2;

	m_optionsPixel.x = (SCREENWIDTH - m_hubTexture->width()) / 2; // Aligned to Hub on purpose
	m_optionsPixel.y = SCREENHEIGHT / 2 + m_hubTexture->height();

	m_pointerTexture->Scale(2.0f);
	m_pointerPixel.x = (SCREENWIDTH - m_hubTexture->width()) / 2 - 2 * m_pointerTexture->width();
}