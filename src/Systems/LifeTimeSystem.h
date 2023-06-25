#ifndef LIFETIMESYSTEM_H
#define LIFETIMESYSTEM_H

#include <SDL2/SDL.h>
#include "entt/entt.hpp"
#include "Components/LifeTime.h"

class LifeTimeSystem
{
public:
    static void Update(std::shared_ptr<entt::registry> registry)
    {
        auto view = registry->view<LifeTime>();
        for (auto entity : view)
        {
            auto lifeTime = view.get<LifeTime>(entity);

            if (SDL_GetTicks() - lifeTime.startTime > lifeTime.duration)
            {
                registry->destroy(entity);
            }
        }
    }
};

#endif