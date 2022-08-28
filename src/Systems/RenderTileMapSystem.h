#ifndef RENDERTILEMAPSYSTEM_H
#define RENDERTILEMAPSYSTEM_H

#include <algorithm>
#include <SDL2/SDL.h>

#include "Components/Sprite.h"
#include "AssetStore/AssetStore.h"

class RenderTileMapSystem
{

public:
    static void Update(std::vector<std::vector<Sprite>> &tileMap, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, SDL_Rect &camera)
    {
        // Filter tiles outside camera
        int xMin = camera.x / (TILESIZE * SCALE);
        int xMax = (camera.x + camera.w) / (TILESIZE * SCALE);
        int yMin = camera.y / (TILESIZE * SCALE);
        int yMax = (camera.y + camera.h) / (TILESIZE * SCALE);

        // tileMap Boundry safeguard
        xMin = std::max(0, xMin);
        xMax = std::min(xMax, static_cast<int>(tileMap.at(0).size()) - 1);
        yMin = std::max(0, yMin);
        yMax = std::min(yMax, static_cast<int>(tileMap.size()) - 1);

        // Render
        for (int y = yMin; y <= yMax; y++)
        {
            for (int x = xMin; x <= xMax; x++)
            {
                const int xPos = x * TILESIZE * SCALE;
                const int yPos = y * TILESIZE * SCALE;
                const Sprite &sprite = tileMap.at(y).at(x);

                SDL_Rect srcRect = sprite.srcRect;
                SDL_Rect dstRect =
                    {
                        static_cast<int>(xPos - camera.x),
                        static_cast<int>(yPos - camera.y),
                        static_cast<int>(sprite.width * SCALE),
                        static_cast<int>(sprite.height * SCALE)};

                SDL_RenderCopyEx(
                    renderer,
                    assetStore->GetTexture(sprite.assetId),
                    &srcRect,
                    &dstRect,
                    0,
                    NULL,
                    sprite.flip);
            }
        }
    }
};

#endif