#include "MainMenu.h"
#include "Constants.h"
#include "Logger/Logger.h"

#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/TextLabel.h"
#include "Components/MenuNavigator.h"

#include "Systems/RenderTextSystem.h"

void MainMenu::Update(double elapsedTime)
{
}

void MainMenu::RenderGraphics(double elapsedTime)
{
	SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
	SDL_RenderClear(m_renderer);
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

	const auto menuNavigator = m_registry->create();
	m_registry->emplace<Transform>(menuNavigator, vec2f(100.0, 100.0));
	m_registry->emplace<MenuNavigator>(menuNavigator, 5);
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
