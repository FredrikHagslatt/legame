#ifndef PROJECTILEEMITSYSTEM_H
#define PROJECTILEEMITSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/Projectile.h"
#include "Components/ProjectileEmitter.h"
#include "Components/Sprite.h"
#include "Components/BoxCollider.h"
#include "Components/Velocity.h"
#include <SDL2/SDL.h>

class ProjectileEmitSystem
{
public:
    static void EmitProjectile(std::shared_ptr<entt::registry> registry, entt::entity entity)
    {
        const auto transform = registry->get<Transform>(entity);
        auto &projectileEmitter = registry->get<ProjectileEmitter>(entity);

        vec2f projectilePosition = transform.position;

        // Adjust projectile spawn pos. (Instead of shooters top left corner)
        if (registry->all_of<Sprite>(entity))
        {
            const auto sprite = registry->get<Sprite>(entity);
            projectilePosition.x += (transform.scale.x * (sprite.width - 4) / 2); // 4 is projectile width. Make dynamic if necessary
            projectilePosition.y += (transform.scale.y * (sprite.height) / 2);
        }

        if (projectileEmitter.inheritDirection && registry->all_of<Velocity>(entity))
        {
            const auto velocity = registry->get<Velocity>(entity);
            projectileEmitter.direction = velocity.lastNonZeroDirection;
        }

        auto projectile = registry->create();
        registry->emplace<Projectile_Tag>(projectile);
        registry->emplace<Transform>(projectile, projectilePosition, vec2f(1.0, 1.0), 0.0);
        registry->emplace<Velocity>(projectile, projectileEmitter.speed, projectileEmitter.direction);
        registry->emplace<Sprite>(projectile, "bullet-image", 4, 4, 4);
        registry->emplace<BoxCollider>(projectile, 4, 4);
        registry->emplace<Projectile>(projectile, projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage, projectileEmitter.duration);
    }

    static void OnKeyPressed(KeyPressedEvent event)
    {
        if (event.keycode == SDLK_SPACE)
        {
            auto registry = event.registry;
            auto view = registry->view<Player_Tag, Transform, Velocity, ProjectileEmitter>();

            for (auto entity : view)
            {
                EmitProjectile(registry, entity);
            }
        }
    }

    static void Update(std::shared_ptr<entt::registry> registry)
    {
        auto view = registry->view<Transform, ProjectileEmitter>();

        for (auto entity : view)
        {
            const auto transform = view.get<Transform>(entity);
            auto &projectileEmitter = view.get<ProjectileEmitter>(entity);

            if (projectileEmitter.repeatFrequency == 0)
            { // Dont fire if repeatrate is 0
                continue;
            }

            if (SDL_GetTicks() - projectileEmitter.lastEmissionTime > projectileEmitter.repeatFrequency)
            {
                EmitProjectile(registry, entity);

                // Update the projectile emitter component last emission to the current milliseconds
                projectileEmitter.lastEmissionTime = SDL_GetTicks();
            }
        }
    }
};

#endif