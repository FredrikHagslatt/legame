#ifndef MENUNAVIGATIONSYSTEM_H
#define MENUNAVIGATIONSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Transform.h"
#include "Components/MenuNavigator.h"
#include "Logger/Logger.h"
#include "Events/KeyPressedEvent.h"

class MenuNavigationSystem
{
public:
    static void Update(std::shared_ptr<entt::registry> registry)
    {
    }

    static void OnKeyPressedEvent(const KeyPressedEvent event)
    {
        const auto registry = event.registry;
        auto view = registry->view<Transform, MenuNavigator>();

        for (auto entity : view)
        {
            auto &transform = view.get<Transform>(entity);
            auto &menuNavigator = view.get<MenuNavigator>(entity);

            switch (event.keycode)
            {
            case SDLK_UP:
                if (menuNavigator.atRow > 0)
                {
                    menuNavigator.atRow--;
                    transform.position.y -= menuNavigator.rowDistance;
                }
                break;
            case SDLK_DOWN:
                if (menuNavigator.atRow < menuNavigator.numRows - 1)
                {
                    menuNavigator.atRow++;
                    transform.position.y += menuNavigator.rowDistance;
                }
                break;
            }
        }
    }
};

#endif