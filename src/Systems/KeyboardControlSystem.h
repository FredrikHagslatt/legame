#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Sprite.h"
#include "Components/Velocity.h"
#include "Components/KeyboardControlled.h"
#include "Events/KeyPressedEvent.h"

namespace KeyBoardControlSystem{

    void OnKeyPressed(KeyPressedEvent event)
    {
        Logger::Info("KeyPressedEvent");

        auto view = event.registry.view<KeyboardControlled, Sprite, Velocity>();
        for (auto entity : view)
        {
            const auto keyboardControl = view.get<KeyboardControlled>(entity);
            auto &sprite = view.get<Sprite>(entity);
            auto &velocity  = view.get<Velocity>(entity);

            switch(event.key)
            {
                case SDLK_UP:
                    velocity.x = keyboardControl.upVelocity.x;
                    velocity.y = keyboardControl.upVelocity.y;
                    sprite.srcRect.y = sprite.height * 0;
                    break;
                case SDLK_RIGHT:
                    velocity.x = keyboardControl.rightVelocity.x;
                    velocity.y = keyboardControl.rightVelocity.y;
                    sprite.srcRect.y = sprite.height * 1;
                    break;
                case SDLK_DOWN:
                    velocity.x = keyboardControl.downVelocity.x;
                    velocity.y = keyboardControl.downVelocity.y;
                    sprite.srcRect.y = sprite.height * 2;
                    break;
                case SDLK_LEFT:
                    velocity.x = keyboardControl.leftVelocity.x;
                    velocity.y = keyboardControl.leftVelocity.y;
                    sprite.srcRect.y = sprite.height * 3;
                    break;

            }

        }

    }

    void Update()
    {

    }

};

#endif