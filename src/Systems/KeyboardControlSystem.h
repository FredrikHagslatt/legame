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
            case SDLK_a:
                velocity.direction.x = -1;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                velocity.direction.x = 1;
                break;
            case SDLK_UP:
            case SDLK_w:
                velocity.direction.y = -1;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                velocity.direction.y = 1;
                break;
            }
            if (velocity.direction != vec2f(0))
            {
                velocity.lastNonZeroDirection = velocity.direction;
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
            case SDLK_w:
                if (velocity.direction.y < 0)
                {
                    velocity.direction.y = 0.0;
                }
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                if (velocity.direction.x > 0)
                {
                    velocity.direction.x = 0.0;
                }
                break;
            case SDLK_DOWN:
            case SDLK_s:
                if (velocity.direction.y > 0)
                {
                    velocity.direction.y = 0.0;
                }
                break;
            case SDLK_LEFT:
            case SDLK_a:
                if (velocity.direction.x < 0)
                {
                    velocity.direction.x = 0.0;
                }
                break;
            }
            if (velocity.direction != vec2f(0))
            {
                velocity.lastNonZeroDirection = velocity.direction;
            }
        }
    }

    static void Update()
    {
    }
};

#endif