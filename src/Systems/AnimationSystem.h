#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Sprite.h"
#include "Components/Animation.h"
#include <SDL2/SDL.h>

extern entt::registry registry;
class AnimationSystem
{
public:
    static void Update()
    {
        auto view = registry.view<Sprite, Animation>();
        for (auto entity : view)
        {
            // Update entity position based on its velocity
            auto &sprite = view.get<Sprite>(entity);
            auto &animation = view.get<Animation>(entity);

            animation.currentFrame = static_cast<int>((SDL_GetTicks() - animation.startTime) * animation.frameRateSpeed / 1000.0) % animation.numFrames;
            sprite.srcRect.x = animation.currentFrame * sprite.width;
        }
    }
};

#endif