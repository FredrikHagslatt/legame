#ifndef CROSSHAIRSYSTEM_H
#define CROSSHAIRSYSTEM_H

#include <string>

#include "Types.h"
#include "entt/entt.hpp"
#include "Logger/Logger.h"

#include "Components/Transform.h"
#include "Components/Tags.h"
#include "Components/Sprite.h"

#include "Events/MouseMotionEvent.h"

class CrosshairSystem
{
public:
    static void Update(std::shared_ptr<entt::registry> registry, SDL_Rect &camera)
    {
        vec2i mousePos;
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        auto view = registry->view<Crosshair_Tag, Transform, Sprite>();
        for (auto entity : view)
        {
            auto &transform = view.get<Transform>(entity);
            transform.position.x = static_cast<float>(mousePos.x + camera.x);
            transform.position.y = static_cast<float>(mousePos.y + camera.y);
        }
    }
};
#endif