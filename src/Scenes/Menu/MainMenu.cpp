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
#include "Events/SceneSwitchEvent.h"

void MainMenu::OnKeyPressedEvent(const KeyPressedEvent event)
{
	const auto menuNavigator = m_registry->get<MenuNavigator>(m_menuNavigator);

	switch (event.keycode)
	{
	case SDLK_RETURN:
		switch (menuNavigator.atRow)
		{
		case 0:
			Logger::Info("[MainMenu] Pressed 'Play Game'");
			Event::dispatcher.trigger(SceneSwitchEvent{"Game", "Garden"});
			break;
		case 1:
			Logger::Info("[MainMenu] Pressed 'Settings'");
			break;
		}
		break;
	}
}

void MainMenu::Update(const double elapsedTime)
{
}

void MainMenu::RenderGraphics(const double elapsedTime)
{
	RenderSystem::Update(m_registry, m_renderer, m_assetStore, m_camera);
	RenderTextSystem::Update(m_registry, m_renderer, m_assetStore, m_camera);
}

void MainMenu::Load()
{
	Logger::Info("[MainMenu] Loading Scene");
	Event::dispatcher.sink<KeyPressedEvent>().connect<&MainMenu::OnKeyPressedEvent>(this);

	m_assetStore->AddFont("charriot-font-40", "assets/fonts/charriot.ttf", 40);
	m_assetStore->AddTexture(m_renderer, "bullet-image", "assets/images/bullet.png");

	m_camera = {0, 0, 0, 0}; // Not used in this Scene. Just here to feed the Systems
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

	m_menuNavigator = m_registry->create();
	m_registry->emplace<UI_Tag>(m_menuNavigator);
	m_registry->emplace<Transform>(m_menuNavigator, vec2f((WINDOWWIDTH - textDimension.x) / 2 - 70, 240.0 + textDimension.y / 2 - 8.0), 1.5);
	m_registry->emplace<MenuNavigator>(m_menuNavigator, 2);
	m_registry->emplace<Sprite>(m_menuNavigator, "bullet-image", 4, 4, 4, true);
}

void MainMenu::Unload()
{
	Event::dispatcher.sink<KeyPressedEvent>().disconnect<&MainMenu::OnKeyPressedEvent>(this);
	auto UIs = m_registry->view<UI_Tag>();
	m_registry->destroy(UIs.begin(), UIs.end());
}
