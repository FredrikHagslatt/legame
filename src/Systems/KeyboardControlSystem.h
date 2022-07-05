#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Sprite.h"
#include "Components/Velocity.h"
#include "Components/KeyboardControlled.h"
#include "Events/KeyPressedEvent.h"

class KeyboardControlSystem
{
public:
    static void OnKeyPressed(const KeyPressedEvent &event)
    {
        enum Direction
        {
            DIR_RIGHT,
            DIR_DOWN,
            DIR_LEFT,
            DIR_UP,
        };

        auto registry = event.registry;
        auto view = registry->view<KeyboardControlled, Sprite, Velocity>();
        for (auto entity : view)
        {
            const auto keyboardControl = view.get<KeyboardControlled>(entity);
            auto &sprite = view.get<Sprite>(entity);
            auto &velocity = view.get<Velocity>(entity);

            switch (event.key)
            {
            case SDLK_UP:
                velocity.x = keyboardControl.upVelocity.x;
                velocity.y = keyboardControl.upVelocity.y;
                sprite.srcRect.y = sprite.height * DIR_UP;
                break;
            case SDLK_RIGHT:
                velocity.x = keyboardControl.rightVelocity.x;
                velocity.y = keyboardControl.rightVelocity.y;
                sprite.srcRect.y = sprite.height * DIR_RIGHT;
                break;
            case SDLK_DOWN:
                velocity.x = keyboardControl.downVelocity.x;
                velocity.y = keyboardControl.downVelocity.y;
                sprite.srcRect.y = sprite.height * DIR_DOWN;
                break;
            case SDLK_LEFT:
                velocity.x = keyboardControl.leftVelocity.x;
                velocity.y = keyboardControl.leftVelocity.y;
                sprite.srcRect.y = sprite.height * DIR_LEFT;
                break;
            }
        }
    }

    static void Update()
    {
    }
};

#endif