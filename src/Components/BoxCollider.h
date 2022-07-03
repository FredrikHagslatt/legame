#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <glm/glm.hpp>

struct BoxCollider
{
    int width;
    int height;
    glm::vec2 offset;

    BoxCollider(
        int width = 0,
        int height = 0,
        glm::vec2 offset = glm::vec2(0))
        : width(width),
          height(height),
          offset(offset)
    {
    }
};

#endif