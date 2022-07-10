#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Sprite.h"
#include "Components/Animation.h"
#include <SDL2/SDL.h>

class AnimationSystem
{
public:
    enum Direction
    {
        DIR_RIGHT,
        DIR_DOWN,
        DIR_LEFT,
        DIR_UP,
    };

    static void Update(std::shared_ptr<entt::registry> registry)
    {
        auto view = registry->view<Sprite, Animation>();
        for (auto entity : view)
        {
            // Update entity position based on its velocity
            auto &sprite = view.get<Sprite>(entity);
            auto &animation = view.get<Animation>(entity);

            if (!registry->all_of<Velocity>(entity))
            {
                animation.currentFrame = static_cast<int>((SDL_GetTicks() - animation.startTime) * animation.frameRateSpeed / 1000.0) % animation.numFrames;
                sprite.srcRect.x = animation.currentFrame * sprite.width;
            }
            else
            {
                const auto velocity = registry->get<Velocity>(entity);
                if (velocity.direction == vec2f(0))
                {
                    animation.currentFrame = 0;
                }
                else
                {
                    animation.currentFrame = static_cast<int>((SDL_GetTicks() - animation.startTime) * animation.frameRateSpeed / 1000.0) % animation.numFrames;
                }
                sprite.srcRect.x = animation.currentFrame * sprite.width;

                if (animation.hasDirections)
                {
                    if (velocity.direction.x != 0.0)
                    {
                        if (velocity.direction.x < 0)
                        {
                            sprite.srcRect.y = sprite.height * DIR_LEFT;
                        }
                        else
                        {
                            sprite.srcRect.y = sprite.height * DIR_RIGHT;
                        }
                    }
                    else
                    {
                        if (velocity.direction.y < 0)
                        {
                            sprite.srcRect.y = sprite.height * DIR_UP;
                        }
                        else if (velocity.direction.y > 0)
                        {
                            sprite.srcRect.y = sprite.height * DIR_DOWN;
                        }
                    }
                }
            }
        }
    }
};

#endif