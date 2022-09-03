#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Logger/Logger.h"
#include <SDL2/SDL.h>
#include "Constants.h"
#include "Game/Game.h"

class CameraMovementSystem
{
public:
    static void Update(std::shared_ptr<entt::registry> registry, SDL_Rect &camera, int mapWidth, int mapHeight)
    {
        auto view = registry->view<Player_Tag, Transform>();
        for (auto entity : view)
        {
            auto const playerTransform = view.get<Transform>(entity);

            if (playerTransform.position.x + (camera.w / 2) < mapWidth)
            {
                camera.x = playerTransform.position.x - (GAMEWINDOWWIDTH / 2);
            }

            camera.x = camera.x < 0 ? 0 : camera.x;
            if (mapWidth < camera.w)
            {
                camera.x = -(GAMEWINDOWWIDTH - mapWidth) / 2;
            }

            if (playerTransform.position.y + (camera.h / 2) < mapHeight)
            {
                camera.y = playerTransform.position.y - (GAMEWINDOWHEIGHT / 2);
            }

            camera.y = camera.y < 0 ? 0 : camera.y;
            if (mapHeight < camera.h)
            {
                camera.y = -(GAMEWINDOWHEIGHT - mapHeight) / 2;
            }
        }
    }
};

#endif