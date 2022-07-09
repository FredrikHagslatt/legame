#include "MainMenu.h"
#include "Constants.h"
#include "Logger/Logger.h"

#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/TextLabel.h"
#include "Components/MenuNavigator.h"

#include "Systems/RenderSystem.h"
#include "Systems/RenderTextSystem.h"

#include "Events/EventDispatcher.h"

void MainMenu::OnKeyPressedEvent(const KeyPressedEvent event)
{
	auto key = event.key;
	switch (key)
	{
	case SDLK_RETURN:
		Logger::Info("MainMenu Enter");
		break;
	}
}

void MainMenu::Update(double elapsedTime)
{
}

void MainMenu::RenderGraphics(double elapsedTime)
{
	SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
	SDL_RenderClear(m_renderer);
	RenderSystem::Update(m_registry, m_renderer, m_assetStore, camera);
	RenderTextSystem::Update(m_registry, m_renderer, m_assetStore, camera);
	SDL_RenderPresent(m_renderer);
}

void MainMenu::Load()
{
	Logger::Info("[MainMenu] Loading Scene");
	Event::dispatcher.sink<KeyPressedEvent>().connect<&MainMenu::OnKeyPressedEvent>(this);

	m_assetStore->AddFont("charriot-font-40", "assets/fonts/charriot.ttf", 40);
	m_assetStore->AddTexture(m_renderer, "bullet-image", "assets/images/bullet.png");

	camera = {0, 0, 0, 0}; // Not used in this Scene. Just here to feed the Systems
	SDL_Color green = {30, 200, 30};

	const auto title = m_registry->create();
	m_registry->emplace<UI_Tag>(title);
	vec2f textDimension = RenderTextSystem::GetTextDimensions(m_renderer, " - Main Menu - ", m_assetStore->GetFont("charriot-font-40"));
	m_registry->emplace<TextLabel>(title, vec2f((WINDOWWIDTH - textDimension.x) / 2, 10), " - Main Menu - ", "charriot-font-40", green, true);

	const auto play = m_registry->create();
	m_registry->emplace<UI_Tag>(play);
	textDimension = RenderTextSystem::GetTextDimensions(m_renderer, "Play Game", m_assetStore->GetFont("charriot-font-40"));
	m_registry->emplace<TextLabel>(play, vec2f((WINDOWWIDTH - textDimension.x) / 2, 240.0), "Play Game", "charriot-font-40", green, true);

	const auto settings = m_registry->create();
	m_registry->emplace<UI_Tag>(settings);
	textDimension = RenderTextSystem::GetTextDimensions(m_renderer, "Settings", m_assetStore->GetFont("charriot-font-40"));
	m_registry->emplace<TextLabel>(settings, vec2f((WINDOWWIDTH - textDimension.x) / 2, 300.0), "Settings", "charriot-font-40", green, true);

	const auto menuNavigator = m_registry->create();
	m_registry->emplace<UI_Tag>(menuNavigator);
	m_registry->emplace<Transform>(menuNavigator, vec2f((WINDOWWIDTH - textDimension.x) / 2 - 70, 240.0 + textDimension.y / 2 - 8.0), 4.0);
	m_registry->emplace<MenuNavigator>(menuNavigator, 2);
	m_registry->emplace<Sprite>(menuNavigator, "bullet-image", 4, 4, 4, true);
}

void MainMenu::Unload()
{
	Event::dispatcher.sink<KeyPressedEvent>().connect<&MainMenu::OnKeyPressedEvent>(this);

	auto UIs = m_registry->view<UI_Tag>();
	m_registry->destroy(UIs.begin(), UIs.end());
}
