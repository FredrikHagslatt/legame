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
    static void OnKeyPressed(KeyPressedEvent event)
    {
        if (event.key == SDLK_SPACE)
        {
            auto registry = event.registry;
            auto view = registry->view<Player_Tag, Transform, Velocity, ProjectileEmitter>();

            for (auto entity : view)
            {
                const auto transform = view.get<Transform>(entity);
                const auto velocity = view.get<Velocity>(entity);
                const auto projectileEmitter = view.get<ProjectileEmitter>(entity);

                vec2f projectilePosition = transform.position;

                if (registry->all_of<Sprite>(entity))
                {
                    const auto sprite = registry->get<Sprite>(entity);
                    projectilePosition.x += (transform.scale.x * sprite.width / 2);
                    projectilePosition.y += (transform.scale.y * sprite.height / 2);
                }

                vec2f projectileVelocity = projectileEmitter.projectileVelocity;
                int directionX = 0;
                int directionY = 0;
                if (velocity.x > 0)
                    directionX = 1;
                if (velocity.x < 0)
                    directionX = -1;
                if (velocity.y > 0)
                    directionY = 1;
                if (velocity.y < 0)
                    directionY = -1;
                projectileVelocity.x = projectileEmitter.projectileVelocity.x * directionX;
                projectileVelocity.y = projectileEmitter.projectileVelocity.y * directionY;

                auto projectile = registry->create();
                registry->emplace<Projectile_Tag>(projectile);
                registry->emplace<Transform>(projectile, projectilePosition, vec2f(1.0, 1.0), 0.0);
                registry->emplace<Velocity>(projectile, projectileVelocity);
                registry->emplace<Sprite>(projectile, "bullet-image", 4, 4, 4);
                registry->emplace<BoxCollider>(projectile, 4, 4);
                registry->emplace<Projectile>(projectile, projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage, projectileEmitter.projectileDuration);
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
                vec2f projectilePosition = transform.position;

                if (registry->all_of<Sprite>(entity))
                {
                    const auto sprite = registry->get<Sprite>(entity);
                    projectilePosition.x += (transform.scale.x * sprite.width / 2);
                    projectilePosition.y += (transform.scale.y * sprite.height / 2);
                }

                auto projectile = registry->create();
                registry->emplace<Projectile_Tag>(projectile);
                registry->emplace<Transform>(projectile, projectilePosition, vec2f(1.0, 1.0), 0.0);
                registry->emplace<Velocity>(projectile, projectileEmitter.projectileVelocity);
                registry->emplace<Sprite>(projectile, "bullet-image", 4, 4, 4);
                registry->emplace<BoxCollider>(projectile, 4, 4);
                registry->emplace<Projectile>(projectile, projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage, projectileEmitter.projectileDuration);

                // Update the projectile emitter component last emission to the current milliseconds
                projectileEmitter.lastEmissionTime = SDL_GetTicks();
            }
        }
    }
};

#endif