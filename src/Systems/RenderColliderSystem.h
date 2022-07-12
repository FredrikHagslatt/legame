#ifndef RENDERCOLLIDERSYSTEM_H
#define RENDERCOLLIDERSYSTEM_H

#include <math.h>
#include <SDL2/SDL.h>
#include "entt/entt.hpp"
#include "Components/Transform.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"

class RenderColliderSystem
{
public:
    static void RenderBoxColliders(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, SDL_Rect &camera)
    {
        auto view = registry->view<Transform, BoxCollider>();
        for (auto entity : view)
        {
            const auto transform = view.get<Transform>(entity);
            const auto collider = view.get<BoxCollider>(entity);

            SDL_Rect colliderRect =
                {
                    static_cast<int>(transform.position.x + collider.offset.x - camera.x),
                    static_cast<int>(transform.position.y + collider.offset.y - camera.y),
                    static_cast<int>(collider.width),
                    static_cast<int>(collider.height)};

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &colliderRect);
        }
    }

    static void RenderCircleColliders(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, SDL_Rect &camera)
    {
        auto view = registry->view<Transform, CircleCollider>();
        for (auto entity : view)
        {
            const auto transform = view.get<Transform>(entity);
            const auto collider = view.get<CircleCollider>(entity);

            vec2f colliderPos = vec2f(transform.position.x + collider.offset.x - camera.x, transform.position.y + collider.offset.y - camera.y);

            for (float angle = 0.0f; angle < 2 * 3.14; angle += 2 * 3.14 / 120)
            {
                SDL_RenderDrawPoint(renderer, colliderPos.x + collider.radius * cosf(angle), colliderPos.y + collider.radius * sinf(angle));
            }
        }
    }

    static void Update(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, SDL_Rect &camera)
    {
        RenderBoxColliders(registry, renderer, camera);
        RenderCircleColliders(registry, renderer, camera);
    }
};

#endif