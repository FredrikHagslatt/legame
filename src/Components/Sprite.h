#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>

struct Sprite
{
    std::string assetId;
    int width;
    int height;
    bool fixedPosition;
    SDL_Rect srcRect;
    SDL_RendererFlip flip;

    Sprite(
        std::string assetId = "",
        int width = 0,
        int height = 0,
        bool fixedPosition = false,
        int srcRectX = 0,
        int srcRectY = 0,
        SDL_RendererFlip flip = SDL_FLIP_NONE)
        : assetId(assetId),
          width(width),
          height(height),
          fixedPosition(fixedPosition),
          flip(flip),
          srcRect({srcRectX,
                   srcRectY,
                   width,
                   height})
    {
    }
};

#endif