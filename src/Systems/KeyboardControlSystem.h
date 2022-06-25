#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "entt/entt.hpp"
#include "EventBus/EventBus.h"
#include "Events/KeyPressedEvent.h"
#include "Components/Sprite.h"
#include "Components/Velocity.h"
#include "Components/KeyboardControlled.h"

namespace KeyBoardControlSystem{

    void SubscribeToEvents(std::unique_ptr<EventBus> &eventBus)
    {
        eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
    }

    void OnKeyPressed(KeyPressedEvent &event)
    {

        auto view = registry.view<KeyboardControlled, Sprite, Velocity>();
        for (auto entity : view)
        {
            const auto keyboardControl = view.get<KeyboardControlled>(entity);
            auto &sprite = view.get<Sprite>(entity);
            auto &velocity  = view.get<Velocity>(entity);

            switch(event.symbol)
            {
                case SDLK_UP:
                    velocity.velocity = keyboardControl.upVelocity;
                    sprite.srcRect.y = sprite.height * 0;
                    break;
                case SDLK_RIGHT:
                    velocity.velocity = keyboardControl.rightVelocity;
                    sprite.srcRect.y = sprite.height * 1;
                    break;
                case SDLK_DOWN:
                    velocity.velocity = keyboardControl.downVelocity;
                    sprite.srcRect.y = sprite.height * 2;
                    break;
                case SDLK_LEFT:
                    velocity.velocity = keyboardControl.leftVelocity;
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