#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Logger/Logger.h"
#include <SDL2/SDL.h>
#include "Constants.h"

extern entt::registry registry;
class CameraMovementSystem
{
public:
    static void Update(SDL_Rect &camera)
    {
        auto view = registry.view<Player_Tag, Transform>();
        for (auto entity : view)
        {
            auto const transform = view.get<Transform>(entity);

            if (transform.position.x + (camera.w / 2) < mapWidth)
            {
                camera.x = transform.position.x - (WINDOWWIDTH / 2);
            }
            if (transform.position.y + (camera.h / 2) < mapHeight)
            {
                camera.y = transform.position.y - (WINDOWHEIGHT / 2);
            }

            camera.x = camera.x < 0 ? 0 : camera.x;
            camera.y = camera.y < 0 ? 0 : camera.y;
            camera.x = camera.x > camera.w ? camera.w : camera.x;
            camera.y = camera.y > camera.h ? camera.h : camera.y;
        }
    }
};

#endif