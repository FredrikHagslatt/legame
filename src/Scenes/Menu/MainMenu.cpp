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
#include "XMLHandler/XMLHandler.h"

void MainMenu::OnKeyPressedEvent(const KeyPressedEvent event)
{
	auto view = m_registry->view<MenuNavigator>();
	for (const auto &entity : view)
	{
		const auto menuNavigator = view.get<MenuNavigator>(entity);
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

	m_camera = {0, 0, 0, 0}; // Not used in this Scene. Just here to feed the Systems
	SDL_Color green = {30, 200, 30};

	//	XMLHandler::SaveToXML(m_registry);
	XMLHandler::LoadFromXML(m_registry, m_renderer, m_assetStore, "assets/levels/menu/MainMenu.xml");
}

void MainMenu::Unload()
{
	Event::dispatcher.sink<KeyPressedEvent>().disconnect<&MainMenu::OnKeyPressedEvent>(this);
	auto UIs = m_registry->view<UI_Tag>();
	m_registry->destroy(UIs.begin(), UIs.end());
}
