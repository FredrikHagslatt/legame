#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include "Types.h"
#include <string>
#include <SDL2/SDL.h>

struct TextLabel
{
    vec2f position;
    std::string text;
    std::string assetId;
    SDL_Color color;
    bool isFixed;

    TextLabel(
        vec2f position = vec2f(0),
        const std::string &text = "",
        const std::string &assetId = "",
        const SDL_Color &color = {0, 0, 0},
        bool isFixed = true)
        : position(position),
          text(text),
          assetId(assetId),
          color(color),
          isFixed(isFixed)
    {
    }
};

#endif