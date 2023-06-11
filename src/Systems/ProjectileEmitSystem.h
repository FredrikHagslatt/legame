#ifndef PROJECTILEEMITSYSTEM_H
#define PROJECTILEEMITSYSTEM_H

#include "Types.h"
#include "entt/entt.hpp"
#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/Projectile.h"
#include "Components/ProjectileEmitter.h"
#include "Components/Sprite.h"
#include "Components/BoxCollider.h"
#include "Components/Velocity.h"

#include "Events/MouseButtonPressedEvent.h"
#include "Events/KeyPressedEvent.h"
#include <SDL2/SDL.h>

class ProjectileEmitSystem
{
public:
    static vec2f GetProjectileSpawnPosition(std::shared_ptr<entt::registry> registry, entt::entity emitterEntity)
    {
        const auto transform = registry->get<Transform>(emitterEntity);
        vec2f projectileSpawnPosition = {transform.position.x, transform.position.y};

        if (registry->all_of<Sprite>(emitterEntity))
        {
            const auto sprite = registry->get<Sprite>(emitterEntity);
            projectileSpawnPosition.x += (transform.scale.x * (sprite.width - 4) / 2);
            projectileSpawnPosition.y += (transform.scale.y * (sprite.height) / 2);
        }
        return projectileSpawnPosition;
    }

    static void EmitProjectile(std::shared_ptr<entt::registry> registry, const entt::entity emitterEntity, const vec2f direction)
    {
        const auto projectileEmitter = registry->get<ProjectileEmitter>(emitterEntity);

        const vec2f projectileSpawnPosition = GetProjectileSpawnPosition(registry, emitterEntity);

        auto projectile = registry->create();
        registry->emplace<Projectile_Tag>(projectile);
        registry->emplace<Transform>(projectile, projectileSpawnPosition, vec2f(1.0, 1.0), 0.0);
        registry->emplace<Velocity>(projectile, projectileEmitter.speed, direction);
        registry->emplace<Sprite>(projectile, "bullet-image", 4, 4);
        registry->emplace<BoxCollider>(projectile, 4, 4);
        registry->emplace<Projectile>(projectile, projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage, projectileEmitter.duration);
    }

    static void EmitProjectileTowardsPosition(std::shared_ptr<entt::registry> registry, const SDL_Rect camera, const entt::entity emitterEntity, const vec2f targetPosition)
    {
        const vec2f projectileSpawnPosition = GetProjectileSpawnPosition(registry, emitterEntity);
        vec2f projectileDirection = targetPosition - projectileSpawnPosition;
        projectileDirection = projectileDirection / projectileDirection.magnitude();
        EmitProjectile(registry, emitterEntity, projectileDirection);
    }

    static void EmitProjectileBasicDirection(std::shared_ptr<entt::registry> registry, const entt::entity emitterEntity)
    {
        const auto transform = registry->get<Transform>(emitterEntity);
        auto &projectileEmitter = registry->get<ProjectileEmitter>(emitterEntity);

        if (projectileEmitter.inheritDirection && registry->all_of<Velocity>(emitterEntity))
        {
            const auto velocity = registry->get<Velocity>(emitterEntity);
            projectileEmitter.direction = velocity.lastNonZeroDirection;
        }

        EmitProjectile(registry, emitterEntity, projectileEmitter.direction);
    }

    static void OnKeyPressed(const KeyPressedEvent event)
    {
        if (event.keycode == SDLK_SPACE)
        {
            auto registry = event.registry;
            auto view = registry->view<Player_Tag, Transform, ProjectileEmitter>();

            for (auto entity : view)
            {
                EmitProjectileBasicDirection(registry, entity);
            }
        }
    }

    struct RegistryCamera
    {
        std::shared_ptr<entt::registry> registry;
        SDL_Rect &camera;
    };

    static void OnMouseButtonPressed(RegistryCamera &registryCamera, const MouseButtonPressedEvent event)
    {
        std::shared_ptr<entt::registry> registry = registryCamera.registry;
        SDL_Rect camera = registryCamera.camera;

        if (event.buttonEvent.button == SDL_BUTTON_LEFT)
        {
            auto playerView = registry->view<Player_Tag, Transform, ProjectileEmitter>();

            for (auto player : playerView)
            {
                auto crosshairView = registry->view<Crosshair_Tag, Transform, Sprite>();

                for (auto crosshair : crosshairView)
                {
                    const auto targetTransform = crosshairView.get<Transform>(crosshair);
                    const auto targetSprite = crosshairView.get<Sprite>(crosshair);
                    EmitProjectileTowardsPosition(registry, camera, player, targetTransform.position);
                }
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
                EmitProjectileBasicDirection(registry, entity);

                // Update the projectile emitter component last emission to the current milliseconds
                projectileEmitter.lastEmissionTime = SDL_GetTicks();
            }
        }
    }
};

#endif