#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Tags.h"
#include "Components/Sprite.h"
#include "Components/Velocity.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"

class KeyboardControlSystem
{
public:
    static void OnKeyPressed(const KeyPressedEvent &event)
    {
        auto registry = event.registry;
        auto view = registry->view<KeyboardControlled_Tag, Sprite, Velocity>();
        for (auto entity : view)
        {
            auto &sprite = view.get<Sprite>(entity);
            auto &velocity = view.get<Velocity>(entity);

            switch (event.keycode)
            {
            case SDLK_LEFT:
                velocity.direction.x = -1;
                //                sprite.srcRect.y = sprite.height * DIR_LEFT;
                break;
            case SDLK_RIGHT:
                velocity.direction.x = 1;
                //                sprite.srcRect.y = sprite.height * DIR_RIGHT;
                break;
            case SDLK_UP:
                velocity.direction.y = -1;
                //                sprite.srcRect.y = sprite.height * DIR_UP;
                break;
            case SDLK_DOWN:
                velocity.direction.y = 1;
                //                sprite.srcRect.y = sprite.height * DIR_DOWN;
                break;
            }
        }
    }

    static void OnKeyReleased(const KeyReleasedEvent &event)
    {
        auto registry = event.registry;
        auto view = registry->view<KeyboardControlled_Tag, Sprite, Velocity>();
        for (auto entity : view)
        {
            auto &sprite = view.get<Sprite>(entity);
            auto &velocity = view.get<Velocity>(entity);

            switch (event.keycode)
            {
            case SDLK_UP:
                if (velocity.direction.y < 0)
                {
                    velocity.direction.y = 0.0;
                }
                break;
            case SDLK_RIGHT:
                if (velocity.direction.x > 0)
                {
                    velocity.direction.x = 0.0;
                }
                break;
            case SDLK_DOWN:
                if (velocity.direction.y > 0)
                {
                    velocity.direction.y = 0.0;
                }
                break;
            case SDLK_LEFT:
                if (velocity.direction.x < 0)
                {
                    velocity.direction.x = 0.0;
                }
                break;
            }
        }
    }

    static void Update()
    {
    }
};

#endif