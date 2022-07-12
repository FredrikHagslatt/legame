#ifndef RENDERCOLLIDERSYSTEM_H
#define RENDERCOLLIDERSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Transform.h"
#include "Components/BoxCollider.h"
#include <SDL2/SDL.h>

class RenderColliderSystem
{
public:
    static void Update(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, SDL_Rect &camera)
    {
        auto view = registry->view<Transform, BoxCollider>();
        for (auto entity : view)
        {
            const auto transform = view.get<Transform>(entity);
            const auto collider = view.get<BoxCollider>(entity);

            /*
                        SDL_Rect colliderRect =
                            {
                                static_cast<int>(transform.position.x - collider.offset.x - camera.x),
                                static_cast<int>(transform.position.y - collider.offset.y - camera.y),
                                static_cast<int>(collider.width * transform.scale.x),
                                static_cast<int>(collider.height * transform.scale.y)};
            */
            SDL_Rect colliderRect =
                {
                    static_cast<int>(transform.position.x - collider.offset.x - camera.x),
                    static_cast<int>(transform.position.y - collider.offset.y - camera.y),
                    static_cast<int>(collider.width),
                    static_cast<int>(collider.height)};

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &colliderRect);
        }
    }
};

#endif