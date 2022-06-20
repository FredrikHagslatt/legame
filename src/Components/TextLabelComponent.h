#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

struct TextLabelComponent
{
    glm::vec2 position;
    std::string text;
    std::string assetId;
    SDL_Color color;
    bool isFixed;

    TextLabelComponent(
        glm::vec2 position = glm::vec2(0),
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