#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <Types.h>

struct BoxCollider
{
    int width;
    int height;
    vec2f offset;

    BoxCollider(
        int width = 0,
        int height = 0,
        vec2f offset = vec2f(0))
        : width(width),
          height(height),
          offset(offset)
    {
    }
};

#endif