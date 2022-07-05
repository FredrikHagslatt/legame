#ifndef PROJECTILELIFECYCLESYSTEM_H
#define PROJECTILELIFECYCLESYSTEM_H

#include <SDL2/SDL.h>
#include "entt/entt.hpp"
#include "Components/Projectile.h"

class ProjectileLifeCycleSystem
{
public:
    static void Update(std::shared_ptr<entt::registry> registry)
    {
        auto view = registry->view<Projectile>();
        for (auto entity : view)
        {
            auto projectile = view.get<Projectile>(entity);

            if (SDL_GetTicks() - projectile.startTime > projectile.duration)
            {
                registry->destroy(entity);
            }
        }
    }
};

#endif